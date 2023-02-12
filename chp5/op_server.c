#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#define BUF_SIZE 1024
#define OP_SIZE 4

void error_handling(char* message);
int calu(int cnt, char op, int num[], int max);
int main(int argc, char* argv[])
{
    int serv_sock, clnt_sock, result, i, op_cnt;
    char opmsg[BUF_SIZE];
    struct sockaddr_in addr_serv, addr_clnt;
    if(argc != 2) {
        printf("Usage : %s <PORT>\n", argv[0]);
        exit(1);
    }

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if(serv_sock == -1)
        error_handling("serv_sock error");

    memset(&addr_serv, 0, sizeof(addr_serv));
    addr_serv.sin_family = AF_INET;
    addr_serv.sin_addr.s_addr = htonl(INADDR_ANY);
    addr_serv.sin_port = htons(atoi(argv[1]));

    if(bind(serv_sock, (struct sockaddr*)&addr_serv, sizeof(addr_serv)) == -1)
        error_handling("bind error");
    if(listen(serv_sock, 5) == -1)
        error_handling("Listen error");
    
    socklen_t addr_clnt_size = sizeof(addr_clnt);

    for(i = 0; i < 5; ++i)
    {
        clnt_sock = accept(serv_sock, (struct sockaddr*)&addr_clnt, &addr_clnt_size);
        if(clnt_sock == -1)
            error_handling("clnt_sock error");
    
        // read(clnt_sock, &opmsg[0], 1);
        // recv_len = 0;
        // int recv_cnt;     
        // while (recv_len < (int)opmsg[0]) {
            // recv_cnt = read(clnt_sock, (int*)&opmsg[recv_len * OP_SIZE + 1], 1);
            // recv_len += recv_cnt;
        // }
        // read(clnt_sock, &opmsg[recv_len + 1], 1);

        read(clnt_sock, (void*)opmsg, BUF_SIZE - 1);

        printf("recv info: %d\n", (int)opmsg[0]);
        for(i = 0; i < (int)opmsg[0]; ++i) {
            printf("recv num: %d\n", (int)opmsg[i*OP_SIZE + 1]);
        }
        printf("the operator: %c\n", opmsg[i * OP_SIZE+1]);

        result = calu((int)opmsg[0], opmsg[i*OP_SIZE +1], (int*)&opmsg[1], 1);
        printf("reslut: %d\n", result);

        write(clnt_sock, (char*)&result, 4);
        puts("Bye Bye");
        close(clnt_sock);
    }

    close(serv_sock);

    return 0;
}

int calu(int cnt, char op, int num[], int max)
{
    int i;
    int ans = 0;

    switch(op){
        case '+':
            for(i =0; i<cnt; ++i)
                ans += num[i];
            break;

        case '-':
            for(i =0; i<cnt; ++i)
                ans -= num[i];
            break;
            
        case '*':
            for(i =0; i<cnt; ++i)
                ans *= num[i];
            break;
            
        case '/':
            for(i =0; i<cnt; ++i)
                ans /= num[i];
            break;
            
        defalut:
            ans = 0;
    }

    return ans;
}

void error_handling(char* message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
