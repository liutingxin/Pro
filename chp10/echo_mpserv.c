#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <signal.h>
#include <sys/wait.h>

#define BUF_SIZE 30
void error_handling(char * message);

void read_child(int sig);

int main(int argc, char* argv[])
{
    if(argc!= 2) 
    {
        printf("Usage : %s <PORT>\n", argv[0]);
        exit(1);
    }
    int sock_serv, sock_clnt;
    socklen_t len = sizeof(sock_clnt);
    struct sockaddr_in addr_serv, addr_clnt;
    struct sigaction act;
    act.sa_handler = read_child;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    sock_serv = socket(PF_INET, SOCK_STREAM, 0);
    sigaction(SIGCHLD, &act, 0);
    memset(&addr_serv, 0, sizeof(addr_serv));
    addr_serv.sin_family = AF_INET;
    addr_serv.sin_addr.s_addr = htonl(INADDR_ANY);
    addr_serv.sin_port = htons(atoi(argv[1]));

    if(bind(sock_serv, (struct sockaddr*)&addr_serv, sizeof(addr_serv)) == -1)
        error_handling("bind error");
    if(!listen(sock_serv, 5) == -1)
        error_handling("listen error");
    
    int str_len;
    char buf[30];
    while(1)
    {
       sock_clnt = accept(sock_serv, (struct sockaddr*)&addr_clnt, &len);
       if(sock_clnt == -1)
           continue;
       else
           puts("new host connected....");
       pid_t pid = fork();
       if(pid == 0)
       {
           close(sock_serv);
            while((str_len = read(sock_clnt, buf, sizeof(buf))) != 0)
            {
                write(sock_clnt, buf, str_len);
            }
            close(sock_clnt);
            puts("disconnect host....");
            return 0;
       }
       else
       {
          close(sock_clnt); 
       }
    }
    close(sock_serv);
    return 0;

}



void read_child(int sig)
{
    pid_t  pid;
    int status;
    pid = waitpid(-1, &status, WNOHANG);
    if(WIFEXITED(status))
        printf("pid: %d, return val: %d\n", pid, WEXITSTATUS(status));
}

void error_handling(char * message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
