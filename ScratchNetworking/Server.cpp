#include "Server.h"

#include <cstdio>

void Server::init_server(unsigned short portNum)
{
    socket.OpenSock(portNum, true);
}

void Server::ServerProcess()
{
    sockaddr_in inetClientAddr;
    inetClientAddr.sin_family = AF_INET;
    int clientSize;

    bool isConnectionOpen;

    char buf[20];

    clientSize = sizeof(inetClientAddr);

    isConnectionOpen = true;

    //loop as long as connection is open
    while (true)
    {
        Address sender;

        //read the incoming data from the connected socket
        if (socket.Receive(sender, buf, sizeof(buf)) > 0)
        {
            //read incoming data
            //make sure the string ends after that by setting  the next byte to null
            //byte to null
            buf[0] = toupper(buf[0]);
            buf[1] = '\0';

            
            printf("Got message from client: %s", buf);

            //send the feedback
            if (sendto(socket.GetSocket(), buf, 5, 0, (sockaddr*)&inetClientAddr, clientSize) == SOCKET_ERROR)
            {
                printf("Error sending message");
                printf("error: %d", WSAGetLastError());
                isConnectionOpen = false;
            }
        }
        /*else if ()
        {
            break;
        }*/
        
    }
}
