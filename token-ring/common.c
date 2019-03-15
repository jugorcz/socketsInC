//
// Created by justyna on 15.03.19.
//

#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "common.h"

char *multicast_ip_address = "224.0.0.1";
int multicast_port = 9010;
int multicastSocket;

void initMulticast() {
    multicastSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if ((multicastSocket = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        printf("Error during init_multicast()\n");
        exit(1);
    }
}

void sendMulticast(char *message, size_t size) {
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(multicast_ip_address);
    addr.sin_port = htons(multicast_port);

    if (sendto(multicastSocket, message, size, 0, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
        printf("Error during multicast send\n");
        exit(1);
    }
}