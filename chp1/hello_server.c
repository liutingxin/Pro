#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>

void error_handling(char * message);

int main(int argc, char* argv[])
{
    int serv_sock;
    int client_sock;

    struct sockaddr_in serv_addr;
    struct sockaddr_in client_addr;
    socklen_t client_size;
    
    char message[] = "Hello world";

    if(argc != 2) {
        printf("Usage : %s <port>", argv[1]);
        exit(1);
    }

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if(serv_sock == -1)
        error_handling("socket error");

    client_size = sizeof(client_addr);
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    if(bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
        error_handling("bind error");

    if(listen(serv_sock, 5) == -1)
        error_handling("listen error");

    client_sock = accept(serv_sock, (struct sockaddr*)&client_addr, &client_size);
    if(client_sock == -1)
        error_handling("client_sock error");
    
    // send(client_sock, message, strlen(message) - 1, 0);
    write(client_sock, message, sizeof(message));

    close(serv_sock);
    close(client_sock);
    return 0;
}


void error_handling(char * message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}