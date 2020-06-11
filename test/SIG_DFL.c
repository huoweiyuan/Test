

#include <signal.h>
#include <stdio.h>
 
int main(void)
{
    /* 使用默认信号处理 */
    raise(SIGTERM);
    printf("Exit main()\n");   /* 决不抵达 */
}
