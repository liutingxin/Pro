#include <stdio.h>
#include <string.h>//for memset function
#include <stdlib.h>//for htons, htonl, atoi function
#include <sys/socket.h>//for socket, bind, listen, accept, recvfrom, sendto function
#include <arpa/inet.h>//for inet_addr, inet_aton, inet_ntoa function 
#include <unistd.h>

#define BUF_SIZE 30

void error_handling(char* message);
int main(int argc, char* argv[])
{
    int sock_serv, str_len;
    socklen_t addr_clnt_size;
    char message[BUF_SIZE];
    struct sockaddr_in addr_serv, addr_clnt;
    if (argc != 3) {
        printf("Usage : %s <IP> <PORT> \n", argv[0]);
        exit(1);
    }
    sock_serv = socket(PF_INET, SOCK_DGRAM, 0);
    if(sock_serv == -1)
        error_handling("socket error");

    memset(&addr_serv, 0, sizeof(addr_serv));
    addr_serv.sin_family = AF_INET;
    addr_serv.sin_addr.s_addr = inet_addr(argv[1]);
    addr_serv.sin_port = htons(atoi(argv[2]));

    addr_clnt_size = sizeof(addr_clnt);
    while (1) {
        fputs("Please input some message: ", stdout);
        fgets(message, BUF_SIZE, stdin);
        if(!strcmp(message, "Q\n") || !strcmp("q\n", message))
            break;
        str_len = sendto(sock_serv, message, strlen(message), 0, (struct sockaddr*)&addr_serv, addr_clnt_size);
        printf("%s__", message);

        recvfrom(sock_serv, message, str_len, 0, (struct sockaddr*)&addr_clnt, &addr_clnt_size);
        // printf("2\n");

        message[str_len] = 0;
        printf("Message form server: %s\n", message);
    } 

    return 0;
}

void error_handling(char* message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}