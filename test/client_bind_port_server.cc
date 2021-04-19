#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <linux/version.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <map>
#include <arpa/inet.h>

int main()
{
  struct sockaddr_in saddr;
  memset(&saddr, 0, sizeof(struct sockaddr_in));

  saddr.sin_family = AF_INET;
  saddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  saddr.sin_port = htons(5546);

  int listenfd = 0;

  if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) > 0 &&
      bind(listenfd,
	   (struct sockaddr*)&saddr, sizeof(struct sockaddr_in)) == 0 &&
      listen(listenfd, 8) == 0)
  {
    struct sockaddr_in rmt_addr;
    socklen_t len = sizeof(rmt_addr);
    int rmtfd = accept(listenfd, (struct sockaddr*)&rmt_addr, &len);
    if (rmtfd == -1)
    {
      // TODO
      return -1;
    }
    char buf[1024];
    while (recv(rmtfd, buf, 1024, 0) > 0)
    {
      printf("%s\n", buf);
    }

  }
 
  return 0;
}
