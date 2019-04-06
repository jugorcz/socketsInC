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
#include <errno.h>

#include "clientTCP.h"

int receivingSocket;
int sendingSocket;
int listeningSocket;
tokenRing_t token;

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
    initListeningSocket();

    //connecting with oneself
    initReceivingSocket();

    //wait for init token from other client
    read(receivingSocket, &token, sizeof(token));

    conf->nextPort = token.port;
    token.msgType = MESSAGE;
    token.value = rand() & 10000;
    printf("Send %d value\n", token.value);

    sendToken(token);
}

void runAsNextClient()
{
    printf("Start work as next client.\n");
    initListeningSocket();
    sendInitToken();
}

void initListeningSocket()
{
    printf("Created socked for listening other clients.\n");
    listeningSocket = initSocket();

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(conf->clientPort);

    if (bind(listeningSocket, (struct sockaddr *) &addr, sizeof(addr)) == -1) {
        printf("%s\n",strerror(errno));
        printf("Error in bind function.\n");
        exit(1);
    }

    //non-blocking
    if (listen(listeningSocket, 10) != 0) {
        printf("%s\n",strerror(errno));
        printf("Error in listen function.\n");
        exit(1);
    }
}

int initSocket()
{
    int s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (s == -1) {
        printf("%s\n", strerror(errno));
        exit(1);
    }
    return s;
}

void initReceivingSocket()
{
    //accept is blocking
    receivingSocket = accept(listeningSocket, NULL, NULL);
    if(receivingSocket == -1)
    {
        printf("Error in accept function.\n");
        printf("%s\n",strerror(errno));
        exit(1);
    }
}

void TCPConnect()
{
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(conf->nextPort);

    //connect is blocking
    int connected = connect(sendingSocket,(struct sockaddr *) &addr, sizeof(addr));
    if(connected == -1)
    {
        printf("Error in connect function\n");
        printf("%s\n",strerror(errno));
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

void sendInitToken()
{
    printf("Send init token.\n");
    tokenRing_t token;
    token.msgType = NEW_USER;
    token.nextPort = conf->nextPort;
    token.port = conf->clientPort;
    sendToken(token);
}

void networkLoop()
{
    while (1) {
        tokenRing_t token;
        initReceivingSocket();
        read(receivingSocket, &token, sizeof(token));

        switch (token.msgType) {
            case NEW_USER:
                printf("Received new_user token\n");
                printf("Got %d\n", token.nextPort);

                if (conf->nextPort == token.nextPort)
                {
                    printf("Switching ports\n");
                    conf->nextPort = token.port;
                }
                else
                    sendToken(token);
                break;

            case MESSAGE:
                sendMulticast(conf->clientID, strlen(conf->clientID) * sizeof(char));
                printf("Received %d\n", token.value);
                token.value = rand() % 10000;
                printf("Sending %d\n", token.value);
                sleep(2);
                sendToken(token);
        }
        if(token.value == 1)
            break;
    }
}
