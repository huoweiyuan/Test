//#include <iostream>
#include <stddef.h>
typedef struct cJSON_Hooks {
      void *(*malloc_fn)(size_t sz);
      void (*free_fn)(void *ptr);
} cJSON_Hooks;

int main()
{
  return 0;
}
