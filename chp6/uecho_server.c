#include <stdio.h>
#include <string.h>//for malloc fuynction
#include <stdlib.h>//for htonl, htons, atoi function
#include <sys/socket.h>//for socket, bind, listen, accept, sendto, recvfrom function
#include <arpa/inet.h>//for inet_addr, inet_aton, inet_ntoa function 
#include <unistd.h>

#define BUF_SIZE 1024

void error_handling(char* message);
int main(int argc, char* argv[])
{
    int sock_serv;
    char message[BUF_SIZE];
    int str_len;
    struct sockaddr_in addr_serv, addr_clnt;
    socklen_t addr_clnt_size;
    if (argc != 2) {
        printf("Usage : %s <PORT>\n",argv[0]);
        exit(1);
    }

    sock_serv = socket(PF_INET, SOCK_DGRAM, 0);
    if(sock_serv == -1)
        error_handling("sock_serv error");

    memset(&addr_serv, 0, sizeof(addr_serv));
    addr_serv.sin_family = AF_INET;
    addr_serv.sin_addr.s_addr = htonl(INADDR_ANY);
    addr_serv.sin_port = htons(atoi(argv[1]));

    if(bind(sock_serv, (struct sockaddr*)&addr_serv, sizeof(addr_serv)) == -1)
        error_handling("bind error");
    
    
    while(1)
    {
        addr_clnt_size = sizeof(addr_clnt);
        str_len = recvfrom(sock_serv, message, BUF_SIZE, 0, (struct sockaddr*)&addr_clnt, &addr_clnt_size);

        sendto(sock_serv, message, str_len, 0,  (struct sockaddr*)&addr_clnt, addr_clnt_size);
    }

    close(sock_serv);
    return 0;
}

void error_handling(char* message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}