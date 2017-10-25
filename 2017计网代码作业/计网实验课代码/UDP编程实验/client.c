#include <winsock2.h>
#include <stdio.h>
#include <time.h>

#define BUFF_SIZE 100
#define SERVER_PORT 1235
#define SERVER_ADDR "172.18.138.80" // 在cmd输入ipconfig获得本机的ipv4地址后，替换该地址

int main() {
    WSADATA wsaData;
    int err = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (err != NO_ERROR) {
        printf("Error at WSAStartup()\n");
        return 1;
    }

    // 创建套接字
    SOCKET sock = socket(PF_INET, SOCK_DGRAM, 0);
    if (sock == INVALID_SOCKET) {
        printf("socket function failed with error: %u\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }
    // 服务器地址信息
    struct sockaddr_in servAddr;
    memset(&servAddr, 0, sizeof(servAddr)); // 用0填充
    servAddr.sin_family = PF_INET;
    servAddr.sin_addr.s_addr = inet_addr(SERVER_ADDR);
    servAddr.sin_port = htons(SERVER_PORT);

    // 发送数据给服务器，接受服务器数据
    struct sockaddr fromAddr;
    int addrLen = sizeof(fromAddr);
    int result = sendto(sock, "Hello!", strlen("Hello!"), 0, (struct sockaddr*)&servAddr, sizeof(servAddr));
    
    if (result == SOCKET_ERROR) {
        printf("socket function failed with error: %u\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }
    
    clock_t start = clock();    // 开始计时
    int counter = 0;            // 接收到包的数量


    for (int i = 0; i < 100; i++) {
        // 设置超过2s未能接受到信息就算超时
        int timeout = 2000; //2s
        int ret = setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout));
    
        char buffer[BUFF_SIZE];
        // 接收服务器信息
        int recv_len = recvfrom(sock, buffer, BUFF_SIZE, 0, &fromAddr, &addrLen);
        buffer[recv_len] = '\0';
        ++counter;
        printf("%s\n", buffer);
    }

    printf("The number of message received from service is %d\n", counter);

    // 关闭套接字
    closesocket(sock);
    WSACleanup();
    return 0;
}
