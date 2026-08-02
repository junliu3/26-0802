// 模拟telnet客户端
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// UNIX/LINUX STD
#include <unistd.h>
#include <netinet/in.h>
#include <pthread.h>
#include <arpa/inet.h>


int main(int argc, char const *argv[])
{
    // 创建套接字、连接、读写、关闭
    int fd = socket(AF_INET, SOCK_STREAM, 0);

    // 连接服务器
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(2000);        // 主机字节序(小端)，转网络字节序(大端)
    // addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);       // 127.0.0.1
    inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);        // 服务器的IP

    // 连接服务器
    int flag = connect(fd, (struct sockaddr *)&addr, sizeof(addr));
    //模拟 telnet
    char buf[128];
    while (1)
    {
        memset(buf, 0, 128);
        printf("#");
        fgets(buf, sizeof(buf) - 1, stdin);
        write(fd, buf, strlen(buf));
        if (!strncmp(buf, "bye", 3))
        {
            break;
        }
        memset(buf, 0, 128);
        read(fd, buf, sizeof(buf));
        printf("收到：%s\n", buf);

    }
    printf("关闭\n");
    close(fd);



    return 0;
}