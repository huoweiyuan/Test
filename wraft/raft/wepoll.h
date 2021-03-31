#ifndef __WEPOLL_H__
#define __WEPOLL_H__
#include <sys/epoll.h>
#include <stdint.h>

#define wepoll_create epoll_create
#define wepoll_create1 epoll_create1
#define wepoll_wait epoll_wait
#define wepoll_pwait epoll_pwait
int wepoll_add(int epfd, int sockfd, uint32_t events);
int wepoll_del(int epfd, int sockfd);
int wepoll_mod(int epfd, int sockfd, uint32_t events);

#endif // __WEPOLL_H__
