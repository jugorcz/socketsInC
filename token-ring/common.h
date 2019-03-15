//
// Created by justyna on 15.03.19.
//

#ifndef TOKEN_RING_COMMON_H
#define TOKEN_RING_COMMON_H

#include <stdlib.h>

typedef struct
{
    char* clientID;
    int clientPort;
    char* nextClientIP;
    int nextPort;
    int startWithToken;
    char* protocol;

} configuration_t;


typedef enum
{
    MESSAGE,
    NEW_USER,
} messageType;

typedef struct
{
    messageType msgType;
    int value;
    int port;
    int nextPort;

} tokenRing_t;


void initMulticast();
void sendMulticast(char* message, size_t size);

#endif //TOKEN_RING_COMMON_H
