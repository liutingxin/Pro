#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>

int main(int argc, char* argvp[])
{
    struct sockaddr_in addr1, addr2;
    char *str_ptr;
    char str_arr[20];

    if(!inet_aton("0x1020304", &addr1.sin_addr))
        perror("error");

    addr2.sin_addr.s_addr = htonl(0x1010101);
    str_ptr = inet_ntoa(addr1.sin_addr);

    strcpy(str_arr, str_ptr);

    printf("Dottd-Decimal notation: %s \n", str_ptr);

    inet_ntoa(addr2.sin_addr);
    //inet_addr这个函数在使用的时候， 会覆盖上一次使用的空间内容， 因此在使用完这个函数后，一定要将暂存指针空间的内容存储到其他空间内
    printf("Dottd-Decimal notation2: %s \n", str_ptr);
    printf("Dottd-Decimal notation3: %s \n", str_arr);

    // printf("Dottd-Decimal notation1: %s \n", inet_ntoa(addr1.sin_addr));
    // printf("Dottd-Decimal notation2: %s \n", inet_ntoa(addr2.sin_addr));
    // printf("Dottd-Decimal notation3: %s \n", inet_ntoa(addr1.sin_addr));


    return 0;
}