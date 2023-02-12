#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>

#define BUF_SIZE 30
void error_handling(char * message);

int main(int argc, char* argv[])
{
    int sd;
    FILE* fp;
    char buf[BUF_SIZE];
    int read_cnt;
    struct sockaddr_in addr_serv;
    socklen_t addr_serv_size = sizeof(addr_serv);

    if(argc != 3) {
        printf("Usage : %s <IP> <PORT>\n", argv[0]);
        exit(1);
    }

    memset(&addr_serv, 0, addr_serv_size);
    addr_serv.sin_family = AF_INET;
    addr_serv.sin_addr.s_addr = inet_addr(argv[1]);
    addr_serv.sin_port = htons(atoi(argv[2]));

    sd = socket(PF_INET, SOCK_STREAM, 0);
    bind(sd, (struct sockaddr*)&addr_serv, addr_serv_size);

    fp = fopen("receive.dat", "w");
    connect(sd, (struct sockaddr*)&addr_serv, addr_serv_size);

    while((read_cnt = read(sd, buf, BUF_SIZE)) != 0)
        fwrite((void*)buf, 1, read_cnt, fp);

    puts("receive data");
    write(sd, "Thank you", 10);

    fclose(fp);
    close(sd);
    return 0;
}


void error_handling(char * message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}