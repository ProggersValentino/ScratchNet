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
    char transmitBuf[1024];
    char receiveBuf[1024];
    
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

            int bytesSent = socket.Send(Address(127,0,0,1, 30000), transmitBuf, sizeof(transmitBuf));

            if(bytesSent <= 0)
            {
                int error = WSAGetLastError();
                printf("didnt send anything cause of this error: %d", error);
            }
            
        }

        //terminate if the letter is q
        if (strcmp(transmitBuf, "q") == 0)
        {
            isConnectionOpen = false;
            break;
        }
        
        Address sender;

        int echoRecieved = socket.Receive(sender, receiveBuf, sizeof(receiveBuf));
        
        if (echoRecieved > 0)
        {
            printf("Got Reply from server: %s\n", receiveBuf);
        }
        
    }
    
}
