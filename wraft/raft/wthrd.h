#ifndef __WTHRD_H__
#define __WTHRD_H__

#include <sys/types.h>
#include <pthread.h>

struct wthrd_attr_arg_s
{
  pthread_attr_t *attr;
  void*(*thrd_func)(void*);
  void *arg;
};

void wthrd_attr_arg_init(struct wthrd_attr_arg_s *attr_arg);
int wthrd_create(pthread_t *thrd_id, const struct wthrd_attr_arg_s *attr_arg);
#define wthrd_join pthread_join
#define  wthrd_detach pthread_detach
int wthrd_detach_self();
#define wthrd_self pthread_self

#endif // __WTHRD_H__
