//
// Created by justyna on 15.03.19.
//

#ifndef TOKEN_RING_COMMON_H
#define TOKEN_RING_COMMON_H

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
