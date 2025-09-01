#pragma once
#include <winsock2.h>

#include "Address.h"

#if defined(WIN32)
#define PLATFORM PLATFORM_WINDOWS
#elif defined(__APPLE__)
#define PLATFORM PLATFORM_MAC
#else
#define PLATFORM PLATFORM_UNIX
#endif


class Socket
{
public:
    Socket();
    ~Socket();

    int GetSocket();
    
    bool OpenSock(unsigned short port, bool bindSock); /*open and bind new socket to a given port*/

    bool OpenUDPClientSock(unsigned short port, char* ipAddress, sockaddr_in*& servAddr);
    void Close(); /*close the socket*/

    bool IsOpen() const;

    /*send packets to a destination*/
    bool Send(const Address& destination, const void* data, int size);

    /*retrieve packets from sender*/
    int Receive(Address& sender, void* data, int size);

private:
    int handle;
};
