#include "wsds.h"

int main()
{
  wsds sds;
  sds = wsds_malloc(11);
  printf("%c", sds[1]);
  return 0;
}
