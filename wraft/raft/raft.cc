#include "raft.h"
#include "raft_impl.h"
#include "wepoll.h"
#include "wthrd.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>


#define RAFT_DEFAUT_PORT (5556)
#define SOCKET_LISTEN_MAX_BACKLOG (7)

using namespace wyhuo;
using std::list;

void raft_option_init(raft_option_s *opt)
{
  opt->election_timeout_ms = 0;
  opt->port = 0;
  opt->host_ipv4 = "";
}

void raft_thrd_main_info_init(raft_thrd_main_info_s *info)
{
  info->running = false;
  info->stop = false;
  info->raft_server = NULL;
}

void raft_sock_init(raft_sock_s *raft_sock)
{
  raft_sock->fd = 0;
}

void raft_ep_option_init(raft_ep_option_s *ep_option)
{
  memset(ep_option, 0, sizeof(raft_ep_option_s));
}

RaftServer::RaftServer()
{
  raft_option_init(&__option);
  raft_ep_option_init(&__ep_option);
  raft_thrd_main_info_init(&__info);
}

RaftServer::~RaftServer()
{
  
}

int RaftServer::init(const raft_option_s &option)
{
  __option = option;
  Consenuse::init();
  StateMachine::init(__option.election_timeout_ms);
}

int RaftServer::start()
{
  int r = server_accept_async();
  return r;
}

int RaftServer::stop()
{
  return (destroy_raft_sockets() |
	  destroy_thrd_main() |
	  destroy_ep_listen());
}

int RaftServer::creat_ep_listen()
{
  struct sockaddr_in saddr;
  memset(&saddr, 0, sizeof(struct sockaddr_in));

  saddr.sin_family = AF_INET;
  saddr.sin_addr.s_addr = inet_addr(__option.host_ipv4.c_str());
  saddr.sin_port = htons(__option.port);

  if ((__ep_option.listenfd = socket(AF_INET, SOCK_STREAM, 0)) > 0 &&
      bind(__ep_option.listenfd,
	   (struct sockaddr*)&saddr, sizeof(struct sockaddr_in)) == 0 &&
      listen(__ep_option.listenfd, SOCKET_LISTEN_MAX_BACKLOG) == 0 &&
      (__ep_option.epfd = wepoll_create(EPOLL_WAIT_MAX_DEFAULT_SIZE)) > 0 &&
      wepoll_add(__ep_option.epfd, __ep_option.listenfd, EPOLLIN | EPOLLET) == 0)
  {
    return 0;
  }
      
  if (__ep_option.epfd != 0)
  {
    close(__ep_option.epfd);
    __ep_option.epfd = 0;
  }
  if (__ep_option.listenfd != 0)
  {
    close(__ep_option.listenfd);
    __ep_option.listenfd = 0;
  }
  return -1;
}

int RaftServer::destroy_ep_listen()
{
  int ret = 0, tmp = 0;
  if (__ep_option.epfd != 0 && (tmp = close(__ep_option.epfd)) == 0)
  {
    __ep_option.epfd = 0;
  }
  ret |= tmp;
  if (__ep_option.listenfd != 0 && (tmp = close(__ep_option.listenfd)) == 0)
  {
    __ep_option.listenfd = 0;
  }
  ret |= tmp;
  return ret == 0 ? 0 : -1;
}

int RaftServer::creat_thrd_main()
{
  pthread_t thrd_id;
  wthrd_attr_arg_s attr_arg;
  wthrd_attr_arg_init(&attr_arg);

  // set options
  __info.raft_server = this;
  attr_arg.thrd_func = thrd_recv;
  attr_arg.arg = static_cast<void*>(&__info);
  
  if (wthrd_create(&thrd_id, &attr_arg) != 0) return -1;
  __info.thrd_id = thrd_id;
  return 0;
}

int RaftServer::destroy_thrd_main()
{
  if (__info.running == true) __info.stop = true;
  void *ret;
  return wthrd_join(__info.thrd_id, &ret);
}

int RaftServer::destroy_raft_sockets()
{
  for (list<raft_sock_s>::iterator iter = __raft_sock_list.begin();
       iter != __raft_sock_list.end();
       ++iter)
  {
    close((*iter).fd);
  }
  __raft_sock_list.clear();
}


int RaftServer::server_accept_async()
{
  if (creat_ep_listen() != 0 &&
      creat_thrd_main() != 0) return -1;
  return 0;
}

void RaftServer::add_raft_sock(const raft_sock_s &raft_sock)
{
  __raft_sock_list.push_back(raft_sock);
}

raft_thrd_main_info_s& RaftServer::get_thrd_info()
{
  return __info;
}

const raft_ep_option_s& RaftServer::get_ep_option() const
{
  return __ep_option; 
}
