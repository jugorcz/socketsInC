//
// Created by justyna on 13.03.19.
//

#include <stdio.h>
#include <sys/socket.h>
#include <zconf.h>
#include "socket.h"

void closeSocket(int socketID)
{
    if(close(socketID) == 0)
        printf("Socked closed successfully.\n");
    else
        printf("Error: cannot close socket.\n");
}