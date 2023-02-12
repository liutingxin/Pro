#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>

void error_handling(char * message);
int main(int argc, char* argv[])
{
  int sock_tcp, sock_udp;
  int sock_type;
  socklen_t optlen;
  int state;

  optlen = sizeof(sock_type);
  sock_tcp = socket(PF_INET, SOCK_STREAM, 0);
  sock_udp = socket(PF_INET, SOCK_DGRAM, 0);
  printf("SOCK_STREAM: %d\n", SOCK_STREAM);
  printf("SOCK_DGRAM: %d\n", SOCK_DGRAM);
  
  state = getsockopt(sock_tcp, SOL_SOCKET, SO_TYPE, (void*)&sock_type, &optlen);
  if(state)
    error_handling("getsocket() error");
  printf("sock_type : %d\n", sock_type);

  state = getsockopt(sock_udp, SOL_SOCKET, SO_TYPE, (void*)&sock_type, &optlen);
  if(state)
    error_handling("getsocket() error");
  printf("sock_type : %d\n", sock_type);

    
  return 0;
}


void error_handling(char * message)
{
  fputs(message, stdout);
  fputc('\n', stderr);
  exit(1);
}
