#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define BUF_SIZE 30
int main()
{
    int fds1[2], fds2[2];
    char str1[] = "who are you";
    char str2[] = "Thank you for your message";
    char buf[BUF_SIZE];
    pid_t pid;
    pipe(fds1); pipe(fds2);

    pid = fork();
    if(pid == 0)
    {
        write(fds1[1], str1, sizeof(str1));
        read(fds2[0], buf, BUF_SIZE);
        printf("Message from fat: %s \n", buf);
    }
    else
    {
        read(fds1[0], buf, BUF_SIZE);
        printf("Message from child: %s \n", buf);
        write(fds2[1], str2, sizeof(str2));
    }

}



