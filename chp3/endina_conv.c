#include <stdio.h>
#include <arpa/inet.h>

int main(int argc, char* argv[])
{
    typedef unsigned short usint;
    typedef unsigned long ulint;

    usint host_port = 0x1234;
    usint net_port;

    ulint host_addr = 0x12345678;
    ulint net_addr;

    net_port = htons(host_port);//转为网络字节序
    net_addr = htonl(host_addr);//转为网络字节序

    printf("Host ordered port: %#x \n", host_port);
    printf("Host ordered port: %#x \n", net_port);
    printf("Host ordered addr: %#lx \n", host_addr);
    printf("Host ordered port: %#lx \n", net_addr);


    return 0;
}
