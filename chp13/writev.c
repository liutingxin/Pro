#include <stdio.h>
#include <string.h>
#include <sys/uio.h>

int main(int argc, char* argv[])
{
    struct iovec vec[2];
    char buf1[] = "ABCDEF";
    char buf2[] = "123456";

    int str_len;

    vec[0].iov_base = buf1;
    vec[1].iov_base = buf2;
    vec[0].iov_len = strlen(buf1);
    vec[1].iov_len = 4;

    str_len = writev(1, vec, 2);
    puts("");
    printf("Write %d Bytes \n", str_len);
    return 0;
}
