#include <stdio.h>
#include <unistd.h>//for close function
#include <sys/types.h>//for open function
#include <sys/stat.h>//for open function
#include <fcntl.h>//for open function
#include <string.h>

#define BUF_SIZE 100

void error_handling(char* message);
int main(int argc, char * argv[])
{
    char buf[BUF_SIZE];
    char* temp;
    int str_len;
    int fd = open(argv[1], O_RDONLY);
    if(fd == -1)
        error_handling("fd error");
    
    str_len = read(fd, buf, BUF_SIZE);

    temp = strtok(argv[1], "./");
    if(str_len != -1)
        printf("the file of %s's information is: %s", temp, buf);
    else
    {
        printf("cannot read target message");
    }

    close(fd);
    return 0;
}


void error_handling(char* message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}