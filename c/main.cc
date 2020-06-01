#include "stack.h"
#include <stdio.h>
int main()
{
  // node_head_t<int> head;
  // stack_init<int>(head);
  // push<int>(head, 1);
  // push<int>(head, 3);
  // push<int>(head, 2);
  // printf("%d ", pop<int>(head));
  // printf("%d ", pop<int>(head));
  // printf("%d ", pop<int>(head));
  // printf("%d ", pop<int>(head));
  Stack<int> stack;
  stack.push(1);
  stack.push(3);
  stack.push(2);
  printf("%d ", stack.pop());
  printf("%d ", stack.pop());
  printf("%d ", stack.pop());
  return 0;
}
