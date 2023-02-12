#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUF_SIZE 30
void error_handling(char * message);

int main(int argc, char* argv[])
{
    int sd_serv, sd_clnt;
    FILE* fp;
    char buf[BUF_SIZE];
    int read_cnt;

    struct sockaddr_in addr_serv, addr_clnt;
    socklen_t addr_clnt_size;    
    if(argc != 2) {
        printf("Usage : %s <PORT>\n", argv[0]);
        exit(1);
    }
    fp = fopen("file_server.c", "r");
    sd_serv = socket(PF_INET, SOCK_STREAM, 0);
    if(sd_serv == -1)
        error_handling("sd_sock error");
    memset(&addr_serv, 0, sizeof(addr_serv));
    addr_serv.sin_family = AF_INET;
    addr_serv.sin_addr.s_addr = htonl(INADDR_ANY);
    addr_serv.sin_port = htons(atoi(argv[1]));

    bind(sd_serv, (struct sockaddr*)&addr_serv, sizeof(addr_serv));
    listen(sd_serv, 5);

    addr_clnt_size = sizeof(addr_clnt);
    sd_clnt = accept(sd_serv, (struct sockaddr*)&addr_clnt, &addr_clnt_size);

    while(1) {
        memset(buf, 0, sizeof(buf));
        read_cnt = fread((void*)buf, 1, BUF_SIZE, fp);

        if(read_cnt < BUF_SIZE) {
            puts(buf);
            // write(sd_clnt, buf, strlen(buf));
            write(sd_clnt, buf, read_cnt);
            break;
        }

        write(sd_clnt, buf, strlen(buf));
    }

    shutdown(sd_clnt, SHUT_WR);
    read(sd_clnt, buf, BUF_SIZE);
    printf("Message from server: %s\n", buf);
    close(sd_serv);
    close(sd_clnt);

    fclose(fp);
    return 0;
}
void error_handling(char * message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}