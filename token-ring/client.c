#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "client.h"
#include "clientTCP.h"
#include "clientUDP.h"

int main(int argc, char** argv) {

    if(argc != 7)
    {
        printf("Error: wrong arguments number, should be 7:\n"
               "\t1: ./client\n"
               "\t2: client id\n"
               "\t3: client port\n"
               "\t4: next client IP\n"
               "\t5: next client port\n"
               "\t6: start with token 0 or 1\n"
               "\t7: protocol TCP or UDP\n");
        return 1;
    }

    /* checking configuration parameters*/
    configuration_t configuration;
    configuration.clientID = argv[1];
    configuration.clientPort = (int)strtol(argv[2], NULL, 10);
    configuration.nextClientIP = argv[3];
    configuration.nextPort = (int)strtol(argv[4], NULL, 10);

    configuration.startWithToken = (int)strtol(argv[5], NULL, 10);
    if( configuration.startWithToken != 0 &&
        configuration.startWithToken != 1)
    {
        printf("Wrong startWithToken argument!\n");
        return 1;
    }

    configuration.protocol = argv[6];
    if( strcmp(configuration.protocol, "TCP") != 0 &&
        strcmp(configuration.protocol, "UDP") != 0)
    {
        printf("Wrong protocol, should be TCP or UDP.\n");
        return 1;
    }

    printf("Client id: %s\n", configuration.clientID);
    printf("Client port: %d\n", configuration.clientPort);
    printf("Next client ip address: %s\n", configuration.nextClientIP);
    printf("Next port: %d\n", configuration.nextPort);
    printf("Starts with token: %s\n",
           configuration.startWithToken == 1 ? "Yes" : "No");
    printf("Protocol: %s\n", configuration.protocol);

    if(strcmp(configuration.protocol, "TCP") == 0)
        runTCPClient(&configuration);
    else
        runUDPClient(&configuration);

    return 0;
}
