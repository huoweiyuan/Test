#ifndef _WTIME_H_
#define _WTIME_H_
#include <stdint.h>

typedef int64_t ustime_t;
typedef int64_t mstime_t;
ustime_t ustime(void);
mstime_t mstime(void);

#endif // _WTIME_H_
