#include <sys/socket.h>

#include "socket.h"

int socketID;

int main()
{
    socketID = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);


    closeSocket(socketID)
}