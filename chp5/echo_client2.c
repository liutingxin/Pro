#include <stdio.h>
#include <stdlib.h>//for htonl, htons function
#include <arpa/inet.h>//for inet_aton, inet_ntoa, inet_addr
#include <sys/socket.h>//for socket, bind, listen, accept, connected....
#include <string.h>
#include <unistd.h>//for read, close function
#define BUF_SIZE 1024

void error_hanling(char* message);
int main(int argc, char* argv[])
{
    int serv_sock, str_len, recv_len, recv_cnt;
    struct sockaddr_in serv_addr;
    char message[BUF_SIZE];
    if(argc != 3) {
        printf("Usage : %s <IP> <PORT>\n", argv[0]);
        exit(1);
    }

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if(serv_sock == -1)
        error_hanling("serv_sock error");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    puts("1");
    if(connect(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
        error_hanling("connect error");
    puts("2");
    
    while(1)
    {
        fputs("please input some message to the server: ", stdout);
        fgets(message, BUF_SIZE, stdin);

        if(!strcmp("Q\n", message) || !strcmp("q\n", message))
            break;

        str_len = write(serv_sock, message, strlen(message));
        recv_len = 0;

        while(recv_len < str_len) {
            recv_cnt = read(serv_sock, &message[recv_len], BUF_SIZE-1);
            if(recv_cnt == -1){
                error_hanling("read error");
            }
            recv_len += recv_cnt;
        }
        message[recv_len] = 0;
        printf("Message form server: %s\n", message);
    
    }
    close(serv_sock);
    return 0;
}


void error_hanling(char* message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}