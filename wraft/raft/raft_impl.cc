#include "raft_impl.h"
#include "raft.h"
#include "wepoll.h"
#include "type.h"
#include "byte_order.h"
#include "wtime.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <linux/version.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <map>
#include <vector>

using std::vector;
using std::map;


#define EP_MAX_EVENTS_DEFAULT (1024)
#define EP_MAX_TIMEOUT_DEFAULT (100) // milliseconds


#define EP_DATA_BUF_DEFAULT_LEN (1024) /// 1k
struct ep_data_struct
{
  int fd;

  uchar *read_cpl; // reading complete
  uint read_cpl_len; // reading complete total len


  uchar *read; // read buffer complete
  uint read_alloc_len; // alloced read buffer tmp
  uint read_pos; // cached read buffer
  uint read_len; // should recv len

  uchar *write;
  uint write_alloc_len;
  uint write_len;
  uint write_pos;
};
typedef struct ep_data_struct ep_data_s;

static int ep_data_init(ep_data_s *ep_data, int buf_default_len)
{
  memset(ep_data, 0, sizeof(ep_data_s));
  ep_data->read = static_cast<uchar*>(malloc(buf_default_len));
  if (ep_data->read == NULL) return -1;
  ep_data->write = static_cast<uchar*>(malloc(buf_default_len));
  if (ep_data->write = NULL) {
    free(ep_data->read);
    return -1;
  }
  ep_data->write_alloc_len = ep_data->read_alloc_len = buf_default_len;
  return 0;
}

static void ep_data_realloc_read(ep_data_s *ep_data, uint realloc_size)
{
  ep_data->read = static_cast<uchar*>(realloc(ep_data->read, realloc_size));
  ep_data->read_alloc_len = realloc_size;
}

static void ep_data_realloc_write(ep_data_s *ep_data, uint realloc_size)
{
  ep_data->write = static_cast<uchar*>(realloc(ep_data->write, realloc_size));
  ep_data->write_alloc_len = realloc_size;
}

static void ep_data_copy_write(ep_data_s *ep_data, const vector<uchar> &block)
{
  ep_data->write_len = block.size();
  if (ep_data->write_alloc_len < ep_data->write_len)
  {
    free(ep_data->write);
    ep_data->write_alloc_len = ep_data->write_len;
    ep_data->write = static_cast<uchar*>(malloc(ep_data->write_alloc_len));
  }
  else if (ep_data->write_len > EP_DATA_BUF_DEFAULT_LEN &&
           ep_data->write_len <= ep_data->write_alloc_len / 2)
  {
    free(ep_data->write);
    ep_data->write_alloc_len /= 2;
    ep_data->write = static_cast<uchar*>(malloc(ep_data->write_alloc_len));
  }
  // else {} // write_len == write_alloc_len
  memcpy(ep_data->write, &block[0], ep_data->write_len);
}

static void ep_data_free_read_cpl(ep_data_s *ep_data)
{
  free(ep_data->read_cpl);
  ep_data->read_cpl = NULL;
  ep_data->read_len = 0;
}

static void ep_data_free_write(ep_data_s *ep_data)
{
  free(ep_data->write);
  ep_data->write_alloc_len = 0;
  ep_data->write_len = 0;
  ep_data->write_pos = 0;
}

static int ep_data_read_complete(ep_data_s *ep_data)
{
  uint orig_read_pos = ep_data->read_pos;
  uint orig_read_len = ep_data->read_len;

  if (orig_read_pos < orig_read_len) return -1; // uncomplete

  ep_data->read_cpl = ep_data->read;
  ep_data->read_cpl_len = orig_read_len;
  ep_data->read = NULL;

  int buf_alloc_len = 0;
  if ((orig_read_pos - orig_read_len) > 4) // uint size |4|
  {
    buf_alloc_len =
      static_cast<uint>(uint4host(ep_data->read_cpl + orig_read_len));
    ep_data->read_len = buf_alloc_len;
  }
  else
  {
    buf_alloc_len = EP_DATA_BUF_DEFAULT_LEN;
    ep_data->read_len = 0;
  }
  ep_data->read = static_cast<uchar*>(malloc(buf_alloc_len));
  ep_data->read_pos = orig_read_pos - orig_read_len;
  ep_data->read_alloc_len = buf_alloc_len;
  return 0; // complete
}

static void ep_data_erase(map<int, ep_data_s> &ep_data_map, int fd)
{
  ep_data_s &ep_data = ep_data_map[fd];
  if (ep_data.read_cpl != NULL) free(ep_data.read_cpl);
  if (ep_data.read != NULL) free(ep_data.read);
  if (ep_data.write != NULL) free(ep_data.write);
  ep_data_map.erase(fd);
}

static int accept_connect(const int &listenfd)
{
  struct sockaddr_in rmt_addr;
  socklen_t len = sizeof(rmt_addr);
  int rmtfd = accept(listenfd, (struct sockaddr*)&rmt_addr, &len);
  if (rmtfd == -1)
  {
    // TODO
    return -1;
  }
  return rmtfd;
}

static void do_ep_set_event(const int &epfd, const int &fd,
                            const wyhuo::ep_event_wish &event)
{
  if (event == wyhuo::epno) return;
  if (event == wyhuo::epin)
  {
    wepoll_mod(epfd, fd, EPOLLIN);
  }
  else if (event == wyhuo::epout)
  {
    wepoll_mod(epfd, fd, EPOLLOUT);
  }
  else if (event == wyhuo::epdel)
  {
    wepoll_del(epfd, fd);
  }
  else
  {
    wepoll_mod(epfd, fd, EPOLLIN | EPOLLOUT);
  }
}

static void do_ep_close(const int &epfd, struct epoll_event &ep_event,
                        wyhuo::RaftServer *server,
                        map<int, ep_data_s> &ep_data_map)
{
  int fd = ep_event.data.fd;
  close(fd);
  ep_data_erase(ep_data_map, fd);
  wepoll_del(epfd, fd);
}

static void do_ep_read(const int &epfd, struct epoll_event &ep_event,
                       wyhuo::RaftServer *server, ep_data_s &ep_data)
{
  wyhuo::ep_event_wish set_ep;
  int len = 0;
  while ((len = recv(ep_event.data.fd, ep_data.read + ep_data.read_pos,
                     ep_data.read_alloc_len - ep_data.read_pos, 0)) <
         ep_data.read_alloc_len - ep_data.read_pos)
  {
    if (len > 0)
    {
      ep_data.read_pos += len;
      if (ep_data.read_len == 0 && ep_data.read_pos >= 4)
      {
        ep_data.read_len = static_cast<uint>(uint4host(ep_data.read));
        if (ep_data.read_len > ep_data.read_alloc_len)
        {
          ep_data_realloc_read(&ep_data, ep_data.read_len);
        }
      }

      if (ep_data_read_complete(&ep_data) == 0)
      {
        // TODO:  server should deal with this block and return a result
        // set epoll to send response
        set_ep = server->parse_block(ep_event.data.fd,
                                     ep_data.read_cpl, ep_data.read_cpl_len);
        do_ep_set_event(epfd, ep_event.data.fd, set_ep);
        ep_data_free_read_cpl(&ep_data);
      }
    }
    else if (len == 0)
    {
      // TODO: shutdown by peer
    }
    else
    {
      switch(errno)
      {
      case EAGAIN: return;
      case EINTR: continue;
      default:
      {
        // TODO : deal with error
        return;
      }
      }
    }
  }
}

static void do_ep_write(const int &epfd, struct epoll_event &ep_event,
                        wyhuo::RaftServer *server, ep_data_s &ep_data)
{
  if (ep_data.write_len == 0)
  {
    vector<uchar> server_block;
    // Get send_block from server. server build block
    server->build_block(ep_event.data.fd, server_block);
    ep_data_copy_write(&ep_data, server_block);
  }

  int send_len = 0;
  while ((send_len = send(ep_event.data.fd, ep_data.write + ep_data.write_pos,
                          ep_data.write_len - ep_data.write_pos, 0)
          ) != ep_data.write_len - ep_data.write_pos)
  {
    if (send_len > 0)
    {
      ep_data.write_pos += send_len;
      if (ep_data.write_pos == ep_data.write_len)
      {
        wyhuo::ep_event_wish set_ep = server->write_done(ep_event.data.fd);
        do_ep_set_event(epfd, ep_event.data.fd, set_ep);
        ep_data_free_write(&ep_data);
        return;
      }
    }
    else if (send_len < 0)
    {
      switch(errno)
      {
      case EAGAIN: return;
      case EINTR: continue;
      default:
      {
        // TODO: deal with error
        return;
      }
      }
    }
    else
    {
    }
  }
}


static void do_use_fd(const int &epfd, struct epoll_event &ep_event,
                      wyhuo::RaftServer *server,
                      map<int, ep_data_s> &ep_data_map)
{
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,17)
  if (ep_event.events & EPOLLRDHUP || ep_event.events & EPOLLERR)
  {
    do_ep_close(epfd, ep_event, server, ep_data_map);
  }
  else if (ep_event.events & EPOLLIN)
#else
  if (ep_event.events & EPOLLIN)
#endif
  {
    do_ep_read(epfd, ep_event, server, ep_data_map[ep_event.data.fd]);
  }
  else if (ep_event.events & EPOLLOUT)
  {
    do_ep_write(epfd, ep_event, server, ep_data_map[ep_event.data.fd]);
  }
  else
  {
    // other event
  }
}


void* thrd_main(void *ptr)
{
  wyhuo::raft_thrd_main_info_s *thrd_info =
    static_cast<wyhuo::raft_thrd_main_info_s*>(ptr);
  wyhuo::RaftServer *server = thrd_info->raft_server;;
  const wyhuo::raft_ep_option_s &ep_opt = server->get_ep_option();
  struct epoll_event events[EPOLL_WAIT_MAX_DEFAULT_SIZE];
  map<int, ep_data_s> ep_data_map;
  int epnum = 0;

  thrd_info->running = true;

  while (thrd_info->stop != true)
  {
    epnum = wepoll_wait(ep_opt.epfd, events,
                        EP_MAX_EVENTS_DEFAULT, EP_MAX_TIMEOUT_DEFAULT);
    if (epnum < 0)
    {
      // TODO
    }
    for (int i = 0; i < epnum; i++)
    {
      if (events[i].data.fd == ep_opt.listenfd)
      {
        int rmtfd = accept_connect(ep_opt.listenfd);
        if (rmtfd != -1 &&
            wepoll_add(ep_opt.epfd, rmtfd, EPOLLET | EPOLLIN | EPOLLRDHUP) == 0)
        {
          // sucess in here. create read/write buf object
          ep_data_s ep_data;
          ep_data_init(&ep_data, EP_DATA_BUF_DEFAULT_LEN);
          ep_data.fd = rmtfd;

          ep_data_map[rmtfd] = ep_data;
        }
      }
      else
      {
        epoll_event &event = events[i];
        do_use_fd(ep_opt.epfd, event, server, ep_data_map);
      }
    }
  }
  thrd_info->running = false;

  return 0;
}




void timer_process(wyhuo::Consenuse *consenuse)
{
  const wyhuo::consenuse_timeout_s &timeout_opt = consenuse->timeout_opt();
  switch (consenuse->get_role())
  {
  case wyhuo::leader:
  {
    // TODO: ping
    break;
  }
  case wyhuo::candidate:
  {
    // TODO: request vote. start a election
    break;
  }
  default: // follower
  {
    // TODO: time out to be candidate
    mstime_t now_ms = mstime();
    if ((now_ms - timeout_opt.__start_election_reset_time_ms) >
        timeout_opt.__start_election_timeout_ms)
    {
      
    }
    
  }
  }
}


void* thrd_consenuse(void *ptr)
{
  wyhuo::consenuse_thrd_info_s *thrd_info =
    static_cast<wyhuo::consenuse_thrd_info_s*>(ptr);
  wyhuo::Consenuse *consenuse = thrd_info->consenuse;
  thrd_info->running = true;
  while (thrd_info->stop != true)
  {
    timer_process(consenuse);
  }
  thrd_info->running = false;
  return 0;
}
