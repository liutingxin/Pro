#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

void error_handling(char * message);
int main(int argc, char* argv[])
{
  int sock;
  int snd_buf =1024 * 3, rec_buf = 1024 *3;
  socklen_t len = sizeof(snd_buf);
  int state;

  sock = socket(PF_INET, SOCK_STREAM, 0);
  state = setsockopt(sock, SOL_SOCKET, SO_SNDBUF, (void*)&snd_buf, len);
  state = setsockopt(sock, SOL_SOCKET, SO_RCVBUF, (void*)&rec_buf, len);
  
  getsockopt(sock, SOL_SOCKET, SO_SNDBUF, (void*)&snd_buf, &len);
  getsockopt(sock, SOL_SOCKET, SO_RCVBUF, (void*)&rec_buf, &len);


  printf("get snd_buf: %d\n", snd_buf);
  printf("get rcv_buf: %d\n", rec_buf);



  return 0;
}






void error_handling(char * message)
{
  fputs(message, stderr);
  fputc('\n', stderr);
  exit(1);
}
