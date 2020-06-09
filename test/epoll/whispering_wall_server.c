/* for test epoll */
// #include "te.h"
#include <stdio.h>

#include <sys/epoll.h>

#include <arpa/inet.h>
#include <sys/socket.h>

#include <string.h>

#include <arpa/inet.h>

#include <netinet/in.h>
int main(int argc, char* argv[])
{
  int listenfd = 0;
  listenfd = socket(AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in serveraddr;
  memset(&serveraddr, 0, sizeof(struct sockaddr_in));
  serveraddr.sin_family = AF_INET;
  const char *host = "127.0.0.1";
  // inet_aton(host, (struct in_addr*)&(serveraddr.sin_addr));
  serveraddr.sin_addr.s_addr = inet_addr(host);
  serveraddr.sin_port = htons(3366);
  bind(listenfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
  listen(listenfd, 20);

  int epfd; // for epoll
  epfd = epoll_create(1024);
  if (epfd < 0) return -1;

  struct epoll_event ev;
  struct epoll_event events[1024];
  ev.data.fd = listenfd;
  ev.events = EPOLLIN | EPOLLOUT;
  epoll_ctl(epfd, EPOLL_CTL_ADD, listenfd, &ev);

  int epnum = 0;
  char buf[1024][256];
  while (1)
  {
    epnum = epoll_wait(epfd, events, 1024, 5);
    for (int i = 0; i < epnum; i++)
    {
      if (events[i].data.fd == listenfd)
      {
        printf("listen\n");
        struct sockaddr_in rmt_addr;
        size_t size = sizeof(rmt_addr);
        int clientfd =
          accept(listenfd, (struct sockaddr*)&rmt_addr, &size);
        ev.data.fd = clientfd;
        ev.events = EPOLLIN | EPOLLOUT | EPOLLET;
        epoll_ctl(epfd, EPOLL_CTL_ADD, clientfd, &ev);
      }
      else if (events[i].events & EPOLLIN)
      {
        printf("EPOLLIN\n");
        int len = recv(events[i].data.fd, buf[i], sizeof(buf[i]), 0);
        if (len < 0)
        {
          
        }
        else if (len > 0)
        {
          len = send(events[i].data.fd, buf[i], len, 0);
          if (len < 0)
          {
            
          }
        }
      }
      else if (events[i].events & EPOLLOUT)
      {
        printf("EPOLLOUT\n");
      }
      else
      {
        printf("EPOLL OTHER\n");
      }
    }
  }
  return 0;
}
