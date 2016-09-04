//
//  tcpserver.c
//  TcpTest
//
//  Created by hexs on 14/9/2.
//  Copyright © 2014年 hexs. All rights reserved.
//

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, const char * argv[]) {

    const char * ip = "192.168.1.105";
    int port = 31951;
    
    struct sockaddr_in address;
    bzero(&address, sizeof(address));
    
    address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &address.sin_addr);
    
    address.sin_port = htons(port);
    
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        printf("socket create failed\r\n");
        return -1;
    }
    
    int ret = bind(sock, (struct sockaddr *)&address, sizeof(address));
    if (ret < 0) {
        printf("bind failed\r\n");
        return -1;
    }
    
    ret = listen(sock, 5);
    if (ret == -1) {
        printf("listen failed\r\n");
        return -1;
    }
    
    struct sockaddr_in client;
    socklen_t client_addrlength = sizeof(client);
    int connectfd = accept(sock, (struct sockaddr *)&client, &client_addrlength);
    if (connectfd < 0) {
        printf("accept failed\r\n");
    } else {
        char data[64] = "I am from shenzhen";
        char buffer[64];
        int i;
        long len;
        for (i = 0; i < 10; ++i) {
            memset(buffer, 0, sizeof(buffer));
            len = recv(connectfd, buffer, sizeof(buffer), 0);
            printf("index is %d len is %ld : %s\r\n",i, len, buffer);
            send(connectfd, data, strlen(data), 0);
        }
        close(connectfd);
    }
    close(sock);
    return 0;
}
