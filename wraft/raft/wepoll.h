#ifndef __WEPOLL_H__
#define __WEPOLL_H__

#include <stdint.h>

int wepoll_add(int epfd, int sockfd, uint32_t events);
int wepoll_del(int epfd, int sockfd);
int wepoll_mod(int epfd, int sockfd, uint32_t events);

#endif // __WEPOLL_H__
