#include "wepoll.h"
#include <sys/epoll.h>

int wepoll_add(int epfd, int sockfd, uint32_t events)
{
  struct epoll_event ev;
  ev.data.fd = sockfd;
  ev.events = events;
  return epoll_ctl(epfd, EPOLL_CTL_ADD, sockfd, &ev);
}

int wepoll_del(int epfd, int sockfd)
{
  return epoll_ctl(epfd, EPOLL_CTL_DEL, sockfd, 0);
}

int wepoll_mod(int epfd, int sockfd, uint32_t events)
{
  struct epoll_event ev;
  ev.data.fd = sockfd;
  ev.events = events;
  return epoll_ctl(epfd, EPOLL_CTL_MOD, sockfd, &ev);
}
