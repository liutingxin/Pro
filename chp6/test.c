#include <stdio.h>
#define  BUF_SIZE 1024

int main()
{
    char message[BUF_SIZE];
    printf("%d\n", sizeof(message));
    printf("%d\n", BUF_SIZE);

    return 0;
}