#include <vector>
#include <string.h>

using namespace std;

struct test
{
  int a;
  int *b;

  /* 不应该在结构体中存在容器时使用memset等操作
     |g++ memset_with_vector.cc -Werror=class-memaccess|

     memset_with_vector.cc: In function ‘int main()’:
     memset_with_vector.cc:16:29: error: ‘void* memset(void*, int, size_t)’ clearing an object of type ‘struct test’ with no trivial copy-assignment; use assignment or value-initialization instead [-Werror=class-memaccess]
     16 |   memset(&t, 0, sizeof(test));
     |                             ^
     memset_with_vector.cc:6:8: note: ‘struct test’ declared here
     6 | struct test
     |        ^~~~
     cc1plus: some warnings being treated as errors
  */
  vector<int > c;

};

int main()
{
  test t;
  memset(&t, 0, sizeof(test));
  return 0;
}
