#include <stdio.h>
#include <netinet/tcp.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

void error_handling(char* message);
int main(int argc, char* argv[])
{

  int sock;
  int snd_buf, rev_buf, state;
  socklen_t len;

  len = sizeof(snd_buf);
  sock = socket(PF_INET, SOCK_STREAM, 0);
  state = getsockopt(sock, SOL_SOCKET, SO_SNDBUF, (void*)&snd_buf, &len);

  printf("snd buf :%d \n", snd_buf);

  state = getsockopt(sock, SOL_SOCKET, SO_RCVBUF, (void*)&snd_buf, &len);
  printf("rec buf :%d \n", snd_buf);

  int optval = 0;
  getsockopt(sock, IPPROTO_TCP, TCP_NODELAY, (void*)&optval, &len); 
  printf("%d\n", optval);
  
  return 0;
} 



void error_handling(char* message)
{
  fputs(message, stderr);
  fputc('\n', stderr);
  exit(1);
}
