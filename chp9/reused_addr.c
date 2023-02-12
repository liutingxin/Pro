#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define TRUE 1
#define FALSE 0
#define BUF_SIZE 30
int main(int argc, char* argv[])
{
  int sock_serv, sock_clnt;
  struct sockaddr_in addr_serv, addr_clnt;
  socklen_t addr_clnt_size = sizeof(addr_clnt);
  char buf[BUF_SIZE];
  int option, str_len;

  if(argc != 2) {
    printf("Usage : %s <PORT>\n", argv[0]);
    exit(1);
  }

  option = TRUE;
  str_len = sizeof(option);
  setsockopt(sock_serv, SOL_SOCKET, SO_REUSEADDR,(void*)&option, str_len);
  sock_serv = socket(PF_INET, SOCK_STREAM, 0);
  memset(&addr_serv, 0, sizeof(addr_serv));
  addr_serv.sin_family = AF_INET;
  addr_serv.sin_addr.s_addr = htonl(INADDR_ANY);
  addr_serv.sin_port = htons(atoi(argv[1]));

  bind(sock_serv, (struct sockaddr*)&addr_serv, sizeof(addr_serv));
  listen(sock_serv, 5);

  sock_clnt = accept(sock_serv, (struct sockaddr*)&addr_clnt, &addr_clnt_size);
  while((str_len = read(sock_clnt, buf, BUF_SIZE)) != 0)
  {
    write(sock_clnt, buf, strlen(buf));
    write(1, buf, str_len);
  } 

  close(sock_clnt);
  close(sock_serv);

  return 0;
}
