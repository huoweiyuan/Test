#ifndef _TE_H_
#define _TE_H_
struct te_event_t
{
  int tefd;
  struct epoll_event *events;
};

struct te_event_loop_t
{
  
};
int te_create(te_event_loop_t *event_loop);
int te_free();
int te_add_event();
int te_del_event();
int te_wait();

#endif // _TE_H_
