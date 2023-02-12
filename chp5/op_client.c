#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#define BUF_SIZE 1024
#define RLT_SIZE 4
#define OPSZ 4

void error_hanling(char* message);
int main(int argc, char* argv[])
{
    int serv_sock, result, op_cnt, i;
    struct sockaddr_in serv_addr;
    char opmsg[BUF_SIZE];
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

    if(connect(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
        error_hanling("connect error");
    else
        puts("Connected......\n");

    fputs("Operand count: ", stdout);
    scanf("%d", &op_cnt);
    opmsg[0] = (char)op_cnt;

    for(i = 0; i < op_cnt; ++i){
        scanf("%d", (int*)&opmsg[1+i*OPSZ]);
    }
    fgetc(stdin);
    fputs("Operator: ", stdout);
    scanf("%c", &opmsg[i*OPSZ + 1]);

    // write(serv_sock, opmsg, strlen(opmsg));
    write(serv_sock, opmsg, op_cnt*OPSZ+2);
    
    read(serv_sock, &result, RLT_SIZE);
    printf("result: %d\n", result);
    close(serv_sock);

    return 0;
}





void error_hanling(char* message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}