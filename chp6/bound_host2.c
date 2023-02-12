#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>
#include <time.h>

#define BUF_SIZE 30
void error_handling(char* message);
int main(int argc, char* argv[])
{
    int sock_serv, str_len = 0;
    char message[BUF_SIZE];
    struct sockaddr_in  addr_clnt;
    socklen_t addr_clnt_size;
    if(argc != 3)
    {
        printf("Usage : %s\n", argv[0]);
        exit(1);
    }

    sock_serv = socket(PF_INET, SOCK_DGRAM, 0);
    memset(&addr_clnt, 0, sizeof(addr_clnt));
    addr_clnt.sin_family = AF_INET;
    addr_clnt.sin_addr.s_addr = inet_addr(argv[1]);
    addr_clnt.sin_port = htons(atoi(argv[2]));
    bind(sock_serv, (struct sockaddr*)&addr_clnt, sizeof(addr_clnt));


    addr_clnt_size = sizeof(addr_clnt);
    for(int i = 0; i < 5; ++i) {
        fgets(message, sizeof(message), stdin);
        // message[strlen(message)] = 0;
        str_len = sendto(sock_serv, message, strlen(message), 0, (struct sockaddr*)&addr_clnt, addr_clnt_size);

        printf("success send %d  bytes message, %d\n", str_len, i);
    }

    return 0;
}

void error_handling(char* message)
{

    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}