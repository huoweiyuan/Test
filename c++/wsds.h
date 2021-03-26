#ifndef __WSDS_H__
#define __WSDS_H__

#include <stdint.h>

template<typename T>
class Sdt
{
 public:
  
};

typedef char* wsds;

wsds wsds_malloc(uint64_t size);
int wsds_free(wsds sds);
char operator[](wsds sds, uint64_t i);

#endif // __WSDS_H__
