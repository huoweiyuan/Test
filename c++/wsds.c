#include "wsds.h"
#include <stdlib.h>

wsds wsds_malloc(uint64_t size)
{
  return (wsds)mallock(size);
}

int wsds_free(wsds sds)
{
  return free(sds);
}

char operator[](wsds sds, uint64_t i)
{
  return 'a';
}
