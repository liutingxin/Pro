#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>

#define BUF_SIZE 100
void error_handling(char *message);
void urg_handle(int sig);

int acpt_sock;
int recv_sock;

int main(int argc, char* argv[])
{
    struct sockaddr_in recv_addr, serv_addr;
    int str_len, state;
    socklen_t serv_addr_size;
    struct sigaction act;
    char buf[BUF_SIZE];
    if (argc != 2)
    {
        printf("Usage :%s <PORT>\n", argv[0]);
        exit(1);
    }

    act.sa_handler = urg_handle;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    acpt_sock = socket(PF_INET, SOCK_STREAM, 0);
    memset(&recv_addr, 0, sizeof(recv_addr));
    recv_addr.sin_family = AF_INET;
    recv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    recv_addr.sin_port = htons(atoi(argv[1]));

    bind(acpt_sock, (struct sockaddr*)&recv_addr, sizeof(serv_addr));
    listen(acpt_sock, 5);

    serv_addr_size = sizeof(serv_addr);
    recv_sock = accept(acpt_sock, (struct sockaddr*)&serv_addr, &serv_addr_size);

    fcntl(recv_sock, F_SETOWN, getpid());
    state = sigaction(SIGURG, &act, 0);

    while((str_len = recv(recv_sock, buf, sizeof(buf), 0)) != 0)
    {
        if(str_len == -1)
        {
            continue;
        }
        buf[str_len] = 0;
        puts(buf);
    }

    close(recv_sock);
    close(acpt_sock);
    return 0;
}


void error_handling(char *message)
{
}
void urg_handle(int sig)
{
    int str_len;
    char buf[BUF_SIZE];
    str_len = recv(recv_sock, buf, BUF_SIZE-1, MSG_OOB);
    buf[str_len] = 0;
    printf("Urgent message : %s\n", buf);
}
