#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <signal.h>

#include <unistd.h>
#define BUF_SIZE 100

int main(int argc, char* argv[])
{
    int sock;
    struct sockaddr_in recv_addr;
    if(argc != 3)
    {
        printf("Usage : %s <IP><PORT>\n", argv[0]);
        exit(1);
    }
    sock = socket(PF_INET, SOCK_STREAM,0);
    memset(&recv_addr, 0, sizeof(recv_addr));
    recv_addr.sin_family = AF_INET;
    recv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    recv_addr.sin_port = htons(atoi(argv[2]));

        
    connect(sock, (struct sockaddr*)&recv_addr, sizeof(recv_addr));
    send(sock, "910", strlen("910"), MSG_OOB);
    write(sock, "123", strlen("123"));
    send(sock, "4", strlen("4") ,MSG_OOB);
    write(sock, "567", 3);
    close(sock);
    return 0;
}
