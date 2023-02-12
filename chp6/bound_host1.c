#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <time.h>

#define BUF_SIZE 30
void error_handling(char* message);
int main(int argc, char* argv[])
{
    int sock_serv, str_len;
    char message[BUF_SIZE];
    struct sockaddr_in addr_serv, addr_clnt;
    socklen_t addr_clnt_size;
    if(argc != 2) {
        printf("Usage : %s <PORT>\n", argv[0]);
        exit(1);
    }

    memset(&addr_serv, 0, sizeof(addr_serv));
    addr_serv.sin_family = AF_INET;
    addr_serv.sin_addr.s_addr = htonl(INADDR_ANY);
    addr_serv.sin_port = htons(atoi(argv[1]));

    sock_serv = socket(PF_INET, SOCK_DGRAM, 0);
    if(sock_serv == -1)
        error_handling("sock error");

    bind(sock_serv, (struct sockaddr*)&addr_serv, sizeof(addr_serv));

    addr_clnt_size = sizeof(addr_clnt);
    for(int i = 0; i < 5; ++i)
    {
        sleep(3);
        str_len = recvfrom(sock_serv, message, sizeof(message), 0, (struct sockaddr*)&addr_clnt, &addr_clnt_size);

        printf("Message from other client: %s", message);
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