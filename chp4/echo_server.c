#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>//for close, read fuction
#include <arpa/inet.h>//for inet_addr, inet_aton function
#include <sys/socket.h>//for socket, bind, listen, accept function

void error_handling(char* message);
int main(int argc, char * argv[])
{
    int serv_sock, clnt_sock;
    struct sockaddr_in serv_addr, clnt_addr;
    socklen_t clnt_size;

    if(argc != 2){
        printf("Usage : %s <port>\n", argv[1]);
        exit(1);
    }

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if(serv_sock == -1)
        error_handling("serv_sock error!");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    if(bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
        error_handling("bind error");

    if(listen(serv_sock, 5) == -1)
        error_handling("listen error");

    clnt_size = sizeof(clnt_addr);
    for(int i = 0; i < 5; ++i) {
        clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_size);
        if(clnt_sock == -1)
            error_handling("clnt_sock error");

        char message[30];
        int str_len;
        while((str_len = read(clnt_sock, message, sizeof(message))) != 0) {
            write(clnt_sock, message, str_len);
        }
        close(clnt_sock);
    }
    close(serv_sock);

    return 0;
}


void error_handling(char* message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
