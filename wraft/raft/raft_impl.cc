#include "raft_impl.h"
#include "raft.h"
#include "wepoll.h"
#include "type.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <linux/version.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define EP_MAX_EVENTS_DEFAULT (1024)
#define EP_MAX_TIMEOUT_DEFAULT (100) // milliseconds


#fdefine EP_DATA_BUF_DEFAULT_LEN (1024) /// 1k
struct ep_data_struct
{
  int fd;
  uchar *read;
  uint read_allo_len;
  uint read_len;
  uchar *write;
  uint write_alloc_len;
  uint write_len;
};
typedef struct ep_data_struct ep_data_s;

int ep_data_init(ep_data_s *ep_data, int buf_default_len)
{
  memset(ep_data, 0, sizeof(ep_data_s));
  ep_data->read = static_cast<uchar*>(malloc(buf_default_len));
  if (ep_data->read == NULL) return -1;
  ep_data->write = static_cast<uchar*>(malloc(buf_default_len));
  if (ep_data->write == NULL)
  {
    free(ep_data->read);
    return -1;
  }
  ep_data.read_alloc_len = ep_data.write_alloc_len = bug_default_len;
  return 0;
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

static void do_ep_close(const int &epfd, struct epoll_event &ep_event,
			wyhuo::RaftServer *server)
{
  close(ep_event.data.fd);
  wepoll_del(epfd, ep_event.data.fd);
}

static void do_ep_read(const int &epfd ,struct epoll_event &ep_event,
		       wyhuo::RaftServer *server, ep_data_s &ep_data)
{
  
  int len = 0;
  while (len = recv(ep_event.data.fd, ep_data.read + ep_data.read_len,
		    ep_data.read_alloc_len - ep_data.read_len, 0))
  {
    if (ep_data.read_len == 0)
    {
      uint block_len = 
    }
  }
}

static void do_ep_write(const int &epfd, struct epoll_event &ep_event,
			wyhuo::RaftServer *server)
{
  
}


static void do_use_fd(const int &epfd, struct epoll_event &ep_event,
		      wyhuo::RaftServer *server, ep_data_s &ep_data)
{
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,17)
  if (ep_event.events & EPOLLRDHUP || ep_event.events & EPOLLERR)
  {
    do_ep_close(epfd, ep_event, server);
  }
  else if (ep_event.events & EPOLLIN)
#else
  if (ep_event.events & EPOLLIN)  
#endif
  {
    do_ep_read(epfd, ep_event, server, ep_data);
  }
  else if (ep_event.events & EPOLLOUT)
  {
    do_ep_write(epfd, ep_event, server);
  }
  else
  {
    // other event
  }
}


void* thrd_recv(void *ptr)
{
  wyhuo::RaftServer *server = static_cast<wyhuo::RaftServer*>(ptr);
  wyhuo::raft_thrd_main_info_s &thrd_info = server->get_thrd_info();
  const wyhuo::raft_ep_option_s &ep_opt = server->get_ep_option();
  struct epoll_event events[EPOLL_WAIT_MAX_DEFAULT_SIZE];
  map<int, ep_data_s> ep_data_map;
  int epnum = 0;

  thrd_info.running = true;
  
  while (thrd_info.stop != true)
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
	ep_data_s &ep_data = ep_data_map[event.data.fd];
	do_use_fd(ep_opt.epfd, event, server, ep_data);
      }
    }
  }
  thrd_info.running = false;
  
  return 0;
}
