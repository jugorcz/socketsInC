//
// Created by justyna on 13.03.19.
//

#ifndef TOKEN_RING_CLIENTTCP_H
#define TOKEN_RING_CLIENTTCP_H

#include "common.h"

void runTCPClient(configuration_t* configuration);
void runAsFirstClient();
void runAsNextClient();

void initListeningSocket();
int initSocket();
void initReceivingSocket();
void TCPConnect();
void sendToken(tokenRing_t token);
void networkLoop();
void sendInitToken();

#endif //TOKEN_RING_CLIENTTCP_H
