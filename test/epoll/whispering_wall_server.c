/* for test epoll */
// #include "te.h"
#include <stdio.h>

#include <sys/epoll.h>

#include <arpa/inet.h>
#include <sys/socket.h>

#include <string.h>

#include <arpa/inet.h>

#include <netinet/in.h>

#include <unistd.h>

#include <errno.h>

static void str_move_forward(char *str, int distance)
{
  int idx = distance;
  while (*(str + idx) != '\0')
  {
    *(str + idx - distance) = *(str + idx);
    idx++;
  }
  *(str + idx - distance) = '\0';
}

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
  ev.events = EPOLLIN | EPOLLET;
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
        socklen_t size = sizeof(rmt_addr);
        int clientfd =
          accept(listenfd, (struct sockaddr*)&rmt_addr, &size);
        ev.data.fd = clientfd;
        ev.events = EPOLLIN | EPOLLET;
        epoll_ctl(epfd, EPOLL_CTL_ADD, clientfd, &ev);
      }
      else if (events[i].events & EPOLLIN)
      {
        printf("EPOLLIN -- ");
        int len = recv(events[i].data.fd, buf[i], sizeof(buf[i]), 0);
        if (len < 0)
        {
          printf("Read error\n");
          
        }
        else if (len > 0)
        {
          printf("get : %s\n", buf[i]);
          ev.data.fd = events[i].data.fd;
          ev.events = EPOLLOUT | EPOLLET;
          epoll_ctl(epfd, EPOLL_CTL_MOD, events[i].data.fd, &ev);
        }
        else
        {
          // len == 0
          printf("Client closed\n");
          ev.data.fd = events[i].data.fd;
          ev.events = EPOLLIN;
          epoll_ctl(epfd, EPOLL_CTL_DEL, events[i].data.fd, &ev);
          close(events[i].data.fd);
        }
        }
      else if (events[i].events & EPOLLOUT)
      {
        printf("EPOLLOUT\n");
        int len = send(events[i].data.fd, buf[i], strlen(buf[i]), 0);
        if (len < 0)
        {
          printf("Send error\n");
          if (errno == EAGAIN)
          {
            printf("EAGAIN\n");
            ev.data.fd = events[i].data.fd;
            ev.events = EPOLLOUT | EPOLLET;
            epoll_ctl(epfd, EPOLL_CTL_MOD, events[i].data.fd, &ev);
          }
        }
        else if (len < strlen(buf[i]))
        {
          printf("len < strlen(buf[i]) %d\n", errno);
          str_move_forward(buf[i], len);
          ev.data.fd = events[i].data.fd;
          ev.events = EPOLLOUT | EPOLLET;
          epoll_ctl(epfd, EPOLL_CTL_MOD, events[i].data.fd, &ev);   
        }
        else
        {
          ev.data.fd = events[i].data.fd;
          ev.events = EPOLLIN | EPOLLET;
          epoll_ctl(epfd, EPOLL_CTL_MOD, events[i].data.fd, &ev);
        }
      }
      else
      {
        printf("EPOLL OTHER\n");
      }
    }
  }
  return 0;
}
