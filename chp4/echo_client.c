#include <stdio.h>
#include <stdlib.h>//for htons, htonl function
#include <unistd.h>//for close, read function
#include <arpa/inet.h>
#include <sys/socket.h>//for socket, bind, listen, accept, function
#include <string.h>

#define BUF_SIZE 1024

void error_handling(char * message);

int main(int argc, char * argv[])
{
    int serv_sock, str_len;
    struct sockaddr_in serv_addr;
    char message[BUF_SIZE];
    
    if(argc != 3) {
        printf("Usage : %s <ip> <port> \n", argv[1]);
        exit(1);
    }

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if(serv_sock == -1)    
        error_handling("serv_sock error");
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    if(connect(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
        error_handling("connected error!");
    else
        puts("Connected.....");

    while(1)
    {
        fputs("Input some message(Q to quit): ", stdout);   
        fgets(message, BUF_SIZE, stdin);

        if(!strcmp(message, "Q\n") || !strcmp(message, "q\n"))
            break;
    
        //从控制台输入的字符，包含最后一个换行， 所以要strlen， 不包括最后的“\0”
        //sizeof 求的是一块空间的总体大小，对指针sizeof就是在求指针的大小，对数字sizeof就是在求数组总空间的大小
        //strlen 求的是实际的内容大小

        write(serv_sock, message, strlen(message));
        //这里用strlen是因为，要将这块空间上的内容发送
        //如果用sizeof的话，会将没有用到的空间的总的大小也用上
        //2、write(fd, buf, strlen(buf));向文件中写入内容的是，只会把缓冲区中的有效内容全部拷贝到文件中。
        //3、write(fd, buf, sizeof(buf));会把缓冲区中的所有数据拷贝到文件中。

        //message中包含换行符，因此它的实际大小要大一个，因此最多只能读取BUF_SIZE - 1个字符
        str_len  = read(serv_sock, message, BUF_SIZE-1);
        message[str_len] = 0;
        printf("The message from server: %s \n", message);
    }    

    close(serv_sock);
    return 0;
}

void error_handling(char * message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}