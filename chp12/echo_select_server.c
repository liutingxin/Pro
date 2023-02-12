#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/time.h>

#define BUF_SIZE 100
void error_handling(char* message);
int main(int argc, char* argv[])
{
    int sock_serv, sock_clnt;
    struct sockaddr_in addr_serv, addr_clnt;
    struct timeval timeout;
    int str_len;
    fd_set reads, cpy_reads;
    socklen_t addr_size;
    char buf[BUF_SIZE];
    if(argc != 2)
    {
        printf("Usage : %s \n", argv[0]);
        exit(1);
    }

    sock_serv = socket(PF_INET, SOCK_STREAM, 0);
    memset(&addr_serv, 0, sizeof(addr_serv));
    addr_serv.sin_family = AF_INET;
    addr_serv.sin_addr.s_addr = htonl(INADDR_ANY);
    addr_serv.sin_port = htons(atoi(argv[1]));
    bind(sock_serv, (struct sockaddr*)&addr_serv, sizeof(addr_serv));
    listen(sock_serv, 5);

    int fd_max, fd_status;

    FD_ZERO(&reads);
    FD_SET(sock_serv, &reads);
    fd_max = sock_serv;

    while(1)
    {
       timeout.tv_sec = 4;
       timeout.tv_usec = 0;
       cpy_reads = reads;

       if((fd_status = select(fd_max + 1, &cpy_reads, 0, 0, &timeout)) == -1)
           break;
       else if(fd_status == 0)
           continue;
      for(int i = 0; i < fd_max + 1; ++i)
      {
          if(FD_ISSET(i, &cpy_reads))
          {
              if(i == sock_serv)
              {
                  sock_clnt = accept(i, (struct sockaddr*)&addr_clnt, &addr_size);
                  FD_SET(sock_clnt, &reads);
                  if(fd_max < sock_clnt)
                      fd_max = sock_clnt;
                  printf("connected new host: %d\n", sock_clnt);
              }
              else{
                  str_len = read(i, buf, sizeof(buf));
                  if(str_len == 0)
                  {
                      FD_CLR(i, &reads);
                      close(i);
                      printf("close client: %d\n", i); 
                  }
                  else
                  {
                      write(i, buf, str_len);
                  }
              }
          }
      }
       
    }
    
    
    close(sock_serv);
    return 0;
}




void error_handling(char* message)
{
}
