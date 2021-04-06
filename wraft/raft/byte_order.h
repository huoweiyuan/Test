#ifndef _BYTE_ORDER_H_
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


inline void uint2net(uchar *T, uint16 A)
{
  if (byte_little_endian_test() == true)
  {
    *(T)=   (uchar)(A);
    *(T+1)= (uchar)(A >> 8);
  }
  *(uint16*)T = A;
}

inline void uint4net(uchar *T, uint32 A)
{
  if (byte_little_endian_test() == true)
  {
    *(T)=  (uchar) (A);
    *(T+1)=(uchar) (A >> 8);
    *(T+2)=(uchar) (A >> 16);
    *(T+3)=(uchar) (A >> 24);   
  }
  *(uint32*)T = A;
}

inline void uint8net(uchar *T, uint64 A)
{
  if (byte_little_endian_test() == true)
  {
    uint4net(T, A);
    uint4net(T+4, A >> 32);
  }
  *(uint64*)T = A;
}

inline uint16 uint2host(const uchar *T)
{
  if (byte_little_endian_test() == true)
  {
    return
      (uint16) (((uint16) (T[0])) +
		((uint16) (T[1]) << 8))
      ;
  }
  return *(uint16*)T;
}


inline uint32 uint4host(const uchar *T)
{
  if (byte_little_endian_test() == true)
  {
    return
      (uint32) (((uint32) (T[0])) +
		(((uint32) (T[1])) << 8) +
		(((uint32) (T[2])) << 16) +
		(((uint32) (T[3])) << 24))
      ;
  }
  return *(uint32*)T;
}


inline uint64 uint8host(const uchar *T)
{
  if (byte_little_endian_test() == true)
  {
    return ((uint64)(((uint32) (T[0])) +
		     (((uint32) (T[1])) << 8) +
		     (((uint32) (T[2])) << 16) +
		     (((uint32) (T[3])) << 24)) +
	    (((uint64) (((uint32) (T[4])) +
			(((uint32) (T[5])) << 8) +
			(((uint32) (T[6])) << 16) +
			(((uint32) (T[7])) << 24))) <<
	     32))
      ;
  }
  return *(uint64*)T;
}



#endif // _BYTE_ORDER_H_
