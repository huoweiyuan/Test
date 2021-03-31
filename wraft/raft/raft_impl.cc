#include "raft_impl.h"
#include "raft.h"
#include "wepoll.h"

#include <sys/socket.h>
#include <netinet/in.h>

#define EP_MAX_EVENTS_DEFAULT (1024)
#define EP_MAX_TIMEOUT_DEFAULT (100) // milliseconds


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

void* thrd_recv(void *ptr)
{
  wyhuo::RaftServer *server = static_cast<wyhuo::RaftServer*>(ptr);
  wyhuo::raft_thrd_main_info_s &thrd_info = server->get_thrd_info();
  const wyhuo::raft_ep_option_s &ep_opt = server->get_ep_option();
  struct epoll_event events[EPOLL_WAIT_MAX_DEFAULT_SIZE];
  int epnum = 0;

  thrd_info.running = true;
  
  while (thrd_info.stop != true)
  {
    epnum = wepoll_wait(ep_opt.epfd, events,
			EP_MAX_EVENTS_DEFAULT, EP_MAX_TIMEOUT_DEFAULT);
    for (int i = 0; i < epnum; i++)
    {
      if (events[i].data.fd == ep_opt.listenfd)
      {
	int rmtfd = accept_connect(ep_opt.listenfd);
	if (rmtfd != -1 &&
	    wepoll_add(ep_opt.epfd, rmtfd, EPOLLIN | EPOLLET) != 0)
	{
	  // TODO
	}
      }
      else if (events[i].data.fd & EPOLLIN)
      {
	
      }
    }
  }
  thrd_info.running = false;
  
  return 0;
}
