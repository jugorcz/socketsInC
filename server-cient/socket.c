
void closeSocket(int socketID)
{
    if(close(socketID) == 0)
        printf("Socked closed successfully.\n");
    else
        printf("Error: cannot close socket.\n");
}