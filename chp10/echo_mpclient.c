#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 30
void error_handling(char *message);
void read_route(int sock, char* buf);
void write_route(int sock, char* buf);

int main(int argc, char* argv[])
{
    int sock;
    char buf[BUF_SIZE];
    struct sockaddr_in addr_serv;
    if(argc != 3)
    {
        printf("Usage : %s <IP> <PORT>\n", argv[0]);
        exit(1);
    }
    memset(&addr_serv, 0, sizeof(addr_serv));
    addr_serv.sin_family = AF_INET;
    addr_serv.sin_addr.s_addr = inet_addr(argv[1]);
    addr_serv.sin_port = htons(atoi(argv[2]));

    sock = socket(PF_INET, SOCK_STREAM, 0);
    if(connect(sock, (struct sockaddr*)&addr_serv, sizeof(addr_serv)) == -1)
        perror("bind error");

    pid_t pid = fork();
    if(pid == 0) {
        write_route(sock, buf);
    } else {
        read_route(sock, buf);
    }

    close(sock);
    return 0;
}


void error_handling(char *message);
void read_route(int sock, char* buf)
{
    while(1)
    {
        int str_len = read(sock, buf, BUF_SIZE);
        if(str_len == 0)
            return;
        buf[str_len] = 0;
        printf("Message from server : %s\n", buf);
    }
}
void write_route(int sock, char* buf)
{
    while(1)
    {
        fgets(buf, BUF_SIZE, stdin);
        if(!strcmp(buf, "Q\n") || !strcmp(buf, "q\n"))
        {
            shutdown(sock, SHUT_WR);
            return;
        }
        write(sock, buf, strlen(buf));
    }
}


