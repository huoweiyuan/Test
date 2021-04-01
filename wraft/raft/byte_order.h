#include _BYTE_ORDER_H_
#define _BYTE_ORDER_H_

#include "type.h"

union endian_test
{
  char ch;
  int i;
};

inline bool byte_little_endian_test()
{
  endian_test test;
  test.i = 0x12345678;
  return (test.ch == 0x78) ? true : false;
}

inline void int2net(uchar *net_byts, int16 host_bytes)
{
  
}

inline int16 int2host(const uchar *net_bytes)
{
  
}

#endif // _BYTE_ORDER_H_
