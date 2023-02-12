#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>

#define BUF_SIZE 30

void read_child(int sig);

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        printf("Usage : %s <PORT>\n", argv[0]);
        exit(1);
    }
    int sock_serv, sock_clnt;
    struct sockaddr_in addr_serv, addr_clnt;
    socklen_t addr_clnt_size = sizeof(addr_clnt);
    char buf[BUF_SIZE];
    struct sigaction act;
    int fds[2];
    int state, str_len;
    pid_t pid;

    memset(&addr_serv, 0, sizeof(addr_serv));
    addr_serv.sin_family = AF_INET;
    addr_serv.sin_addr.s_addr = htonl(INADDR_ANY);
    addr_serv.sin_port = htons(atoi(argv[1]));

    sock_serv = socket(PF_INET, SOCK_STREAM, 0);
    if(sock_serv == -1)
        perror("SOCK error");

    act.sa_handler = read_child;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    state = sigaction(SIGCHLD, &act, 0);

    if(bind(sock_serv, (struct sockaddr*)&addr_serv, sizeof(addr_serv)) == -1)
        perror("bind error");
    if(listen(sock_serv, 5) == -1)
        perror("listen error");

    pipe(fds);
    pid = fork();
    if(pid == 0)
    {
        FILE* fp = fopen("echomsg.txt", "w+");
        char message[BUF_SIZE];

        for(int i = 0; i < 10; ++i)
        {
            str_len = read(fds[0], message, sizeof(message));
            fwrite((void*)message, 1, str_len, fp);

        }
        fclose(fp);
        return 0;
    }

    while(1)
    {
        sock_clnt = accept(sock_serv, (struct sockaddr*)&addr_clnt, &addr_clnt_size);
        if(sock_clnt == -1)
            continue;
        else
            puts("new hosts connected...");
        pid = fork();
        if(pid == 0)
        {
            close(sock_serv);
            while((str_len = read(sock_clnt, buf, sizeof(buf))) !=  0)
            {
                write(fds[1], buf, str_len);
                write(sock_clnt, buf, str_len);
            }
            close(sock_clnt);
            puts("client disconnected....");
            return 0;
        }
        else
        {
            close(sock_clnt);
        }
    }

    close(sock_serv);
    return 0;
}



void read_child(int sig)
{
    int status;
    pid_t pid = waitpid(-1, &status, WNOHANG);
    printf("remove child :%d \n", pid);
}
