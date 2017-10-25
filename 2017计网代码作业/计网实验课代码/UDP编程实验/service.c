#include <winsock2.h>
#include <stdio.h>

#define BUFF_SIZE 100
#define SERVER_PORT 1235
#define SERVER_ADDR "127.0.0.1" // 手动输入服务器的ip地址

int main() {
    WSADATA wsaData;
    int err = WSAStartup(MAKEWORD(2, 2), &wsaData); // 搜索相应的socket库
    if (err != NO_ERROR) {
        printf("Error at WSAStartup()\n");
        return 1;
    }
    
    // 创建套接字
    SOCKET sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock == INVALID_SOCKET) {
        printf("socket function failed with error: %u\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    // 绑定套接字
    struct sockaddr_in servAddr;
    memset(&servAddr, 0, sizeof(servAddr));                 // 每个字节都用0填充
    servAddr.sin_family = PF_INET;                          // IPV4地址
    // servAddr.sin_addr.s_addr = inet_addr(SERVER_ADDR);   // 手动输入程序的ip地址
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);           //  自动获取IP地址
    servAddr.sin_port = htons(SERVER_PORT);                 // 端口
    int result = bind(sock, (SOCKADDR*)&servAddr, sizeof(SOCKADDR));     // 绑定
    if (result == SOCKET_ERROR) {
        printf("socket function failed with error: %u\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }
    
    // 接收客户端请求
    SOCKADDR clntAddr;      // 客户端地址信息
    int nSize = sizeof(SOCKADDR);
    char buffer[BUFF_SIZE];
    recvfrom(sock, buffer, BUFF_SIZE, 0, &clntAddr, &nSize); // 接受来自客户端的信息

    printf("Receive message from clinet: %s\n", buffer);
    printf("Sending message...\n");

    // 循环向客户端发送100条"i : Hello world"的信息
    for (int i = 0; i < 100; i++) {
        char send_msg[BUFF_SIZE];
        sprintf(send_msg, "%d : Hello world", i);
        sendto(sock, send_msg, strlen(send_msg), 0, &clntAddr, nSize);
    }

    // 关闭套接字
    closesocket(sock);
    WSACleanup();
    printf("Done!\n");
    return 0;
}