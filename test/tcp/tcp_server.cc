#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#define PORT 8888
#define BACKLOG 2

void process_conn_server(int s)
{
  ssize_t size = 0;
  char buffer[1024];
  while(1)
  {
    size = read(s, buffer,1024);
    if(size == 0) return;
    std::cout << buffer << std::endl;
    // sprintf(buffer, "%d bytes altogether\n",size);
    // write(s, buffer, strlen(buffer)+1);
  }
}

int main()
{
  int ss,sc; //socket server,socket client
  struct sockaddr_in server_addr;
  struct sockaddr_in client_addr;
  int err;
  pid_t pid;

  //create AF_INET socket
  ss = socket(AF_INET, SOCK_STREAM, 0);
  if(ss<0)
  {
    printf("socket error\n");
    return -1;
  }

  //set server address
  bzero(&server_addr,sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  server_addr.sin_port = htons(PORT);

  err = bind(ss, (struct sockaddr*)&server_addr , sizeof(server_addr) );
  if(err < 0)
  {
    printf("bind error\n");
    return -1;
  }

  err = listen(ss,BACKLOG);
  if(err < 0)
  {
    printf("listen error\n");
    return -1;
  }

  while(1)
  {
    socklen_t addrlen = sizeof(struct sockaddr);
    sc = accept(ss, (struct sockaddr*)&client_addr, &addrlen);
    if(sc < 0)
    {
      continue;
    }

    pid = fork();
    if(pid == 0)
    {
      close(ss);
      process_conn_server(sc);
    }
    else
    {
      close(sc);
    }
  }
}
// ————————————————
// 版权声明：本文为CSDN博主「harry_502」的原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接及本声明。
// 原文链接：https://blog.csdn.net/harry_502/article/details/69063097
