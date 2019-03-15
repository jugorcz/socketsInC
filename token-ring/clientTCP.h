//
// Created by justyna on 13.03.19.
//

#ifndef TOKEN_RING_CLIENTTCP_H
#define TOKEN_RING_CLIENTTCP_H

#include "client.h"
#include "tokenRing.h"
#include "common.h"

void runTCPClient(configuration_t* configuration);
void runAsFirstClient();
void runAsNextClient();

int initReceivingSocket();
int initSocket();
int initAcceptSocket();
void TCPConnect();
void sendToken(tokenRing_t token);
void networkLoop();

#endif //TOKEN_RING_CLIENTTCP_H
