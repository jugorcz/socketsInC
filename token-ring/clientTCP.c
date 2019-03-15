//
// Created by justyna on 13.03.19.
//

#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <memory.h>

#include "clientTCP.h"

int receivingSocket;
int sendingSocket;
int acceptSocket;
tokenRing_t token;
int nextPort;


configuration_t* conf;

void runTCPClient(configuration_t* configuration)
{
    conf = configuration;
    printf("\n----------TCP client----------\n");
    initMulticast();

    if(conf->startWithToken == 1)
        runAsFirstClient();
    else
        runAsNextClient();

    networkLoop();
}

void runAsFirstClient()
{
    receivingSocket = initReceivingSocket();
    sendingSocket = initSocket();

    //connecting with oneself
    acceptSocket = initAcceptSocket();

    //wait for init token from other client
    read(acceptSocket, &token, sizeof(token));

    nextPort = token.port;
    token.msgType = MESSAGE;
    token.value = rand() & 10000;
    printf("Send %d value\n", token.value);

    sendToken(token);
}

void runAsNextClient()
{

}

int initReceivingSocket()
{
    int recSocket = initSocket();

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(conf->clientPort);

    if (bind(recSocket, (struct sockaddr *) &addr, sizeof(addr)) != 0) {
        exit(1);
    }

    if (listen(recSocket, 10) != 0) {
        exit(1);
    }

    return recSocket;
}

int initSocket()
{
    int s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (s == -1)
        exit(1);
    return s;
}

int initAcceptSocket()
{
    //accept is blocking
    int s = accept(receivingSocket, NULL, NULL);
    if(s == -1)
    {
        printf("Error in accept function.\n");
        exit(1);
    }
    return s;
}


void TCPConnect()
{
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(nextPort);

    //connect is blocking
    int connected = connect(sendingSocket,(struct sockaddr *) &addr, sizeof(addr));
    if(connected == -1)
    {
        printf("\n");
        exit(1);
    }
}


void sendToken(tokenRing_t token)
{
    sendingSocket = initSocket();
    TCPConnect();
    write(sendingSocket, &token, sizeof(token));
    close(sendingSocket);

}

void networkLoop()
{
    while (1) {
        tokenRing_t token;
        acceptSocket = initAcceptSocket();
        read(acceptSocket, &token, sizeof(token));

        switch (token.msgType) {
            case NEW_USER:
                printf("Received new_user token\n");
                printf("Got %d\n", token.nextPort);

                if (nextPort == token.nextPort)
                {
                    printf("Swithicng ports\n");
                    nextPort = token.port;
                }
                else
                    sendToken(token);
                break;

            case MESSAGE:
                sendMulticast(conf->clientID, strlen(conf->clientID) * sizeof(char));
                printf("Received %d\n", token.value);
                token.value = rand() % 10000;
                printf("Sending %d\n", token.value);
                sleep(1);
                sendToken(token);
        }
        if(token.value == 1)
            break;
    }
}
