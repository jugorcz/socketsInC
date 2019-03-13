//
// Created by justyna on 13.03.19.
//

#include <sys/socket.h>
#include <netinet/in.h>

#include "socket.h"

int socketID;

int main()
{
    socketID = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);


    closeSocket(socketID);
}