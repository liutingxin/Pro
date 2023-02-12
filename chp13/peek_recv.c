#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>


#define BUF_SIZE 30

int main(int argc, char * argv[])
{
    int acpt_sock, recv_sock;
    struct sockaddr_in addr_serv, addr_clnt;
    socklen_t addr_size;
    int str_len;
    char buf[BUF_SIZE];

    if(argc != 2)
    {
        printf("Usage :%s <PORT>\n", argv[0]);
        exit(1);
    }

    recv_sock = socket(PF_INET, SOCK_STREAM, 0);
    memset(&addr_serv, 0, sizeof(addr_serv));
    addr_serv.sin_family = AF_INET;
    addr_serv.sin_addr.s_addr = htonl(INADDR_ANY);
    addr_serv.sin_port = htons(atoi(argv[1]));
    bind(recv_sock, (struct sockaddr*)&addr_serv, sizeof(addr_serv));
    listen(recv_sock, 5);

    addr_size = sizeof(addr_clnt);
    acpt_sock = accept(recv_sock, (struct sockaddr*)&addr_clnt, &addr_size);
    puts("connect");

    while(1)
    {
        str_len = recv(acpt_sock, buf, BUF_SIZE - 1, MSG_PEEK|MSG_DONTWAIT);
        if(str_len >0)
            break;
    }
    buf[str_len] = 0;
    printf("Buf read message: %s\n", buf);


    str_len = recv(acpt_sock, buf, BUF_SIZE - 1, 0);
    buf[str_len] = 0;
    printf("read  again message: %s\n", buf);

    close(acpt_sock);
    close(recv_sock);
    return 0;
}
