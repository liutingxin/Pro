#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define BUF_SIZE 30

int main(int argc, char* argv[])
{
    int sock_serv;
    struct sockaddr_in addr_serv, addr_clnt;
    if(argc != 3)
    {
        printf("Usage : %s <IP> <PORT> \n", argv[0]);
        exit(1);
    }
    sock_serv = socket(PF_INET, SOCK_STREAM, 0);
    memset(&addr_serv, 0, sizeof(addr_serv));
    addr_serv.sin_family = AF_INET;
    addr_serv.sin_addr.s_addr = inet_addr(argv[1]);
    addr_serv.sin_port = htons(atoi(argv[2]));

    connect(sock_serv, (struct sockaddr*)&addr_serv, sizeof(addr_serv));

    write(sock_serv, "123", strlen("123"));

    close(sock_serv);
    return 0;

}
