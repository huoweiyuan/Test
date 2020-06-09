#include <stdio.h>

#include <arpa/inet.h>
#include <sys/socket.h>

#include <string.h>

#include <arpa/inet.h>

#include <netinet/in.h>

#include <errno.h>
#define HOST "127.0.0.1"
#define PORT (3366)

int main()
{
  int clet_socket = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in clet_addr;
  memset(&clet_addr, 0, sizeof(clet_addr));
  clet_addr.sin_family = AF_INET;
  clet_addr.sin_addr.s_addr = inet_addr(HOST);
  clet_addr.sin_port = htons(PORT);
  int r =
    connect(clet_socket, (struct sockaddr*)&clet_addr, sizeof(clet_addr));
  if (r < 0)
  {
    printf("%s\n", strerror(errno));
    return -1;
  }

  char statment[1024], whisper_statment[1024];
  while (scanf("%s", statment))
  {
    int len = send(clet_socket, statment, strlen(statment), 0);
    if (len < 0)
    {
      return -1;
    }
    len = recv(clet_socket, whisper_statment, 1024, 0);
    whisper_statment[len] = '\0';
    printf("whispering: %s\n", whisper_statment);
  }
  return 0;
}
