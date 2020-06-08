#include "te.h"
#include <stdio.h>
#include <assert.h>

#include <sys/epoll.h>
#include <unistd.h>

int te_create(loop_t *event_loop)
{
  assert(event_loop != NULL);
  event_loop->te.tefd = epoll_create(event_loop->size);
  if (event_loop->te.tefd < 0)
  {
    return -1;
  }
  return 0;
}

int te_free(loop_t *event_loop)
{
  assert(event_loop != NULL);
  return close(event_loop->te.tefd);
}

int te_add_event(loop_t *event_loop)
{
  
  return 0;
}

