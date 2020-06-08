#ifndef _TE_H_
#define _TE_H_
struct te_event_t
{
  int tefd;
  struct epoll_event *events;
};
typedef struct te_event_t te_t;

struct te_event_loop_struct
{
  unsigned int size;
  te_t te;
};
typedef struct te_event_loop_struct loop_t;

int te_create(loop_t *event_loop);
int te_free(loop_t *event_loop);
int te_add_event(loop_t *event_loop);
int te_del_event();
int te_wait();

#endif // _TE_H_
