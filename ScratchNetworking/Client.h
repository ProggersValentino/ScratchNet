#pragma once
#include "Socket.h"

class Client
{
public:
    Socket socket;

    sockaddr_in* inetServerAddr;
    int servLen = sizeof(inetServerAddr);
    
    void InitClient(unsigned short int port, char* ip);
    void ClientProcess();
    
};
