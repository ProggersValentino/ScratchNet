#include "Client.h"
#include <iostream>
#include <limits>

void Client::InitClient(unsigned short int port, char* ip)
{
    socket.OpenSock(port, false);
}

void Client::ClientProcess()
{
    bool isConnectionOpen;

    //separate buffers to prevent mix ups and ensure there is a clear difference between what gets sent and what is retrieved from server
    char transmitBuf[100];
    char receiveBuf[100];

    strcpy_s(transmitBuf, "");
    strcpy_s(receiveBuf, "");

    isConnectionOpen = true;

    while (isConnectionOpen)
    {
        std::cout << "Message to send: " << std::endl;
        
        
        //get the string to send
        if (std::cin.getline(transmitBuf, sizeof(transmitBuf)))
        {
            /*//send the transmit buffer to the socket
            if (sendto(socket.GetSocket(), transmitBuf, 2, 0, (sockaddr*) &inetServerAddr, sizeof(servLen)) == SOCKET_ERROR)
            {
                isConnectionOpen = false;
                break;
            }*/

            socket.Send(Address(127,0,0,1, 30000), transmitBuf, sizeof(transmitBuf));
            
        }

        //terminate if the letter is q
        if (strcmp(transmitBuf, "q") == 0)
        {
            isConnectionOpen = false;
            break;
        }
        
        Address sender;
        
        if (socket.Receive(sender, receiveBuf, sizeof(receiveBuf)) > 0)
        {
            printf("Got Reply from server: %s\n", receiveBuf);
        }
        else
        {
            isConnectionOpen = false;
        }
        
    }
    
}
