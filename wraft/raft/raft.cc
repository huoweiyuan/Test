#include "raft.h"
#include "raft_impl.h"
#include "wepoll.h"
#include "wthrd.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>



#define EPOLL_WAIT_MAX_DEFAULT_SIZE (7)
#define RAFT_DEFAUT_PORT (5556)
#define SOCKET_LISTEN_MAX_BACKLOG (7)

using namespace wyhuo;

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

RaftServer::RaftServer()
  : __epfd(0),
    __listenfd(0)
{
  raft_option_init(&__option);
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

int RaftServer::creat_ep_listen()
{
  struct sockaddr_in saddr;
  memset(&saddr, 0, sizeof(struct sockaddr_in));

  saddr.sin_family = AF_INET;
  saddr.sin_addr.s_addr = inet_addr(__option.host_ipv4.c_str());
  saddr.sin_port = htons(__option.port);

  if ((__listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
  {
    goto err_lab;
  }
      
  if (bind(__listenfd, (struct sockaddr*)&saddr, sizeof(struct sockaddr_in)) != 0)
  {
    goto err_lab;
  }

  if (listen(__listenfd, SOCKET_LISTEN_MAX_BACKLOG) != 0)
  {
    goto err_lab;
  }

  if ((__epfd = epoll_create(EPOLL_WAIT_MAX_DEFAULT_SIZE)) < 0)
  {
    goto err_lab;
  }

  if (wepoll_add(__epfd, __listenfd, EPOLLIN | EPOLLET) != 0)
  {
    goto err_lab;
  }

  return 0;

 err_lab:
  if (__epfd != 0)
  {
    close(__epfd);
    __epfd = 0;
  }
  if (__listenfd != 0)
  {
    close(__listenfd);
    __listenfd = 0;
  }
  return -1;
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


int RaftServer::server_accept_async()
{
  if (creat_ep_listen() != 0 &&
      creat_thrd_main() != 0) return -1;
  return 0;
}
