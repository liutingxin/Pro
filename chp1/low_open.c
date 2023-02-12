#include <stdio.h>
#include <sys/stat.h>//for open function
#include <sys/types.h>//for open function
#include <fcntl.h>//for open function

#include <unistd.h> //for close function

void error_handling(char * message);

int main()
{
    int fd = open("./lowOpenTest.txt", O_CREAT | O_TRUNC | O_WRONLY);
    char buf[] = "let's go!\n";

    if(fd == -1)
        error_handling("fd error");

    printf("the file descriptor is %d \n", fd);

    if(write(fd, buf, sizeof(buf)) == -1)
        error_handling("write error");
    else
        printf("write ok\n");

    close(fd);
    return 0;
}

void error_handling(char * message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
