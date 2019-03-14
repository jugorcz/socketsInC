//
// Created by justyna on 14.03.19.
//

#ifndef TOKEN_RING_CLIENT_H
#define TOKEN_RING_CLIENT_H

typedef struct
{
    char* clientID;
    int clientPort;
    char* nextClientIP;
    int nextPort;
    int startWithToken;
    char* protocol;

} configuration_t;

#endif //TOKEN_RING_CLIENT_H
