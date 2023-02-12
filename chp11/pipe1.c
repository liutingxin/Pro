#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#define BUF_SIZE 30

int main()
{
    int fds[2];
    char buf[]= "who are you";

    pid_t pid = fork();
    if(pid == 0)
    {
        write(fds[1], buf, strlen(buf));
    }
    else 
    {
        sleep(1);
        char b[BUF_SIZE];
        read(fds[0], b, BUF_SIZE);
        puts(b);
    }
    return 0;
}





