#include <assert.h>
#include <iostream>
int test(int i) {
  std::cout << i << std::endl;
  assert(false);
  return 1;
}

int main() {
  test(1);
  return 0;
}
