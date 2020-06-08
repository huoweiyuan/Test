/* for test epoll */
// #include "te.h"
#include <stdio.h>

#include <sys/epoll.h>

int main(int argc, char* argv[])
{
  int listenfd = 0;
  listenfd = socket(AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in serveraddr;
  bzero(&serveraddr, sizeof(struct sockaddr_in));
  serveraddr.sin_famliy = AF_INET;
  inet_aton("127.0.0.1", &(serveraddr.sin_addr));
  serveraddr.sin_port = htons(5566);
  bind(listenfd, (sockaddr*)&serveraddr, sizeof(serveraddr));
  listen(listenfd, 20);

  
  int epfd; // for epoll
  epfd = epoll_create(1024);
  if (epfd < 0) return -1;

  struct epoll_event ev;
  ev.data.fd = listenfd;
  ev.events = EPOLLIN | EPOLLOUT;
  epoll_ctl(epfd, EPOLL_CTL_ADD, listenfd, &ev);

  while (1)
  {
    // TODO
  }
  return 0;
}
