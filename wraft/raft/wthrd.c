#include "wthrd.h"
#include <string.h>

void wthrd_attr_arg_init(struct wthrd_attr_arg_s *attr_arg)
{
  memset(attr_arg, 0, sizeof(struct wthrd_attr_arg_s));
}

int whtrd_create(pthread_t *thrd_id, const struct wthrd_attr_arg_s *attr_arg)
{
  return
    pthread_create(thrd_id, attr_arg->attr, attr_arg->thrd_func, attr_arg->arg);
}

int whtrd_detach_self()
{
  return wthrd_detach(wthrd_self());
}
