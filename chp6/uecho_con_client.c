#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUF_SIZE 30

void error_handling(char* message);
int main(int argc, char* argv[])
{
    int sock;
    char message[BUF_SIZE];
    int str_len;
    socklen_t addr_sz;
    struct sockaddr_in addr_serv, addr_clnt;
    if(argc != 3){
        printf("Usage : %s <IP> <PORT>\n", argv[0]);
        exit(1);
    }

    sock = socket(PF_INET, SOCK_DGRAM, 0);
    memset(&addr_serv, 0, sizeof(addr_serv));
    addr_serv.sin_family = AF_INET;
    addr_serv.sin_addr.s_addr = inet_addr(argv[1]);
    addr_serv.sin_port = htons(atoi(argv[2]));

    connect(sock, (struct sockaddr*)&addr_serv, sizeof(addr_serv));

    while(1) {
        fputs("Insert message(q to quit)", stdout);

        fgets(message, sizeof(message), stdin);
        if(!strcmp(message, "q\n") || !strcmp("Q\n", message))
            break;
        
        write(sock, message, strlen(message));

        str_len = read(sock, message, sizeof(message));
        message[str_len] = 0;
        printf("message from server: %s\n", message);
    }

    close(sock);
    return 0;
}

void error_handling(char* message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}