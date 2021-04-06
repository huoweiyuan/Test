#include "wtime.h"
#include <sys/time.h>

ustime_t ustime(void)
{
  struct timeval tv;
  gettimeofday(&tv, 0);
  return tv.tv_sec * 1000000 + tv.tv_usec;
}

mstime_t mstime(void)
{
  return ustime() / 1000;
}
