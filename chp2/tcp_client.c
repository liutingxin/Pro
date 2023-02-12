#include <stdio.h>
#include <unistd.h>//for close, read function
#include <arpa/inet.h>
#include <sys/socket.h>//for socket, bind, accept, listen funcion
#include <stdlib.h>
#include <string.h>

void error_handling(char* message);

int main(int argc, char* argv[])
{
    int sock;
    struct sockaddr_in serv_addr;
    char message[30];
    int str_len=0, idx=0, read_len =0;

    if(argc != 3 ) {
        printf("Usage : %s <ip> <port>\n", argv[1]);
        exit(1);
    }

    sock = socket(PF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)    
        error_handling("connect error");
    
    while((read_len = read(sock, &message[idx++], 1)))
    {//every time 
        if(read_len == -1)
            error_handling("read error");
        str_len += read_len;   
    }

    printf("message from server: %s\n", message);
    printf("Function read call count: %d\n", str_len);

    close(sock);

    return 0;
}

void error_handling(char* message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
