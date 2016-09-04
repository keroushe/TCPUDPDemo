//
//  udpclient.c
//  TcpTest
//
//  Created by hexs on 14/9/2.
//  Copyright © 2014年 hexs. All rights reserved.
//

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>

#include <arpa/inet.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>

#define PORT_SERVER 8888

int main(int argc,char * argv[])
{
    struct sockaddr_in addr_server,addr_client;
    const char *ip = "192.168.1.105";
    
    int s = socket(AF_INET, SOCK_DGRAM, 0);
    
    bzero(&addr_server, sizeof(addr_server));
    inet_pton(AF_INET, ip, &addr_server.sin_addr);
    addr_server.sin_family = AF_INET;
    addr_server.sin_port = htons(PORT_SERVER);
    
    char data[64] = "where are you from ?";
    char buffer[64];
    int i;
    int len = sizeof(addr_server);
    for (i = 0; i < 10; ++i) {
        memset(buffer, 0, sizeof(buffer));
        sendto(s, data, strlen(data), 0, (struct sockaddr *)&addr_server, len);
        recvfrom(s, buffer, sizeof(buffer), 0, (struct sockaddr *)&addr_client, (socklen_t *)&len);
        printf("index is %d : %s \r\n",i, buffer);
    }
    close(s);
    
    return 0;
}