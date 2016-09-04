//
//  tcpclient.c
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
    
    struct sockaddr_in server_address;
    bzero(&server_address, sizeof(server_address));
    
    server_address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &server_address.sin_addr);
    
    server_address.sin_port = htons(port);
    
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        printf("socket create failed\r\n");
        return -1;
    }
    
    int ret = connect(sockfd, (struct sockaddr *)&server_address, sizeof(server_address));
    if (ret < 0) {
        printf("connect failed\r\n");
        return -1;
    }
    
    char data[64] = "where are you from ?";
    char buffer[64];
    int i;
    long len;
    for (i = 0; i < 10 ; ++i) {
        memset(buffer, 0, sizeof(buffer));
        send(sockfd, data, strlen(data), 0);
        
        len = recv(sockfd, buffer, sizeof(buffer), 0);
        printf("index is %d len is %ld : %s\r\n",i, len, buffer);
    }
    close(sockfd);
    return 0;
}
