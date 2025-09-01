#pragma once
#include <winsock2.h>

#include "Socket.h"

class Server
{
public:
    Socket socket;

    void init_server(unsigned short portNum);
    
    void ServerProcess();
};
