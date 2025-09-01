#include "Socket.h"
#include <iostream>
#include <winsock.h>
#include <ws2tcpip.h>

Socket::Socket()
{
    handle = 0;
}

Socket::~Socket()
{
}

int Socket::GetSocket()
{
    return handle;
}

bool Socket::OpenSock(unsigned short port, bool bindSock)
{
    /*socket creation*/
    handle = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    
    if (handle <= 0)
    {
        std::cout << "Socket creation failed." << std::endl;
        return false;
    }
    
    sockaddr* Addr; 
    sockaddr_in* inetAddr;

    //allocate memory for the address structure and set it to zero
    Addr = (sockaddr*) malloc(sizeof(sockaddr));
    memset((char*) Addr, 0, sizeof(sockaddr));
    
    /*filling the address structure*/
    Addr->sa_family = AF_INET;

    inetAddr = (sockaddr_in*) Addr;
    inetAddr->sin_addr.s_addr = htonl(INADDR_ANY); /*loopback ip address*/
    inetAddr->sin_port = htons((unsigned short)port);

    /*binding the address to the socket we created making the socket's destination implicite in future calls*/
    if (bindSock && bind(handle, (sockaddr*)&inetAddr, sizeof(&inetAddr)) != SOCKET_ERROR)
    {
        std::cout << "Socket bind failed." << std::endl;
        std::cout << "Error: " << WSAGetLastError() << std::endl;
        return false;
    }

    if (!bindSock) return true; //early exit as we dont need to make not blocking
    
    /*
    set socket to non block as by default its turned which means that recvfrom function will not return until a packet is available to read
     * which ofc is not suitable when we need to simulate 60 frames per second therefore it would be to slow
     /*#1#*/
#if PLATFORM == PLATFORM_WINDOWS
    DWORD nonBlocking = 1;

    if (ioctlsocket(handle, FIONBIO, &nonBlocking) != 0)
    {
        std::cout << "ioctlsocket failed. failed to set socket to non-blocking" << std::endl;
        return false;
    }
#endif

    
    return true;
}

void Socket::Close()
{
    /*clos the socket*/
#if PLATFORM == PLATFORM_WINDOWS
    closesocket(handle);
#endif
}

bool Socket::IsOpen() const
{
    return handle != 0;
}

bool Socket::Send(const Address& destination, const void* data, int size)
{
    
    sockaddr_in address;
    /*settings for the address we want to send to*/
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(destination.getAddress()); /*loopback ip address*/
    address.sin_port = htons(destination.getPort());
    
    /*sending a packet to a specific address*/
    int sent_bytes = sendto(handle, (const char*) data, size, 0, (const sockaddr*) &address, sizeof(address));
    
    if (sent_bytes != size)
    {
        int error = WSAGetLastError();
        printf("failed to send data to socket, error: %d\n", error);
        
        return false;
    }
    else
    {
        printf("successfully sent data to socket\n");
    }

    return true;
}

int Socket::Receive(Address& sender, void* data, int size)
{
#if PLATFORM == PLATFORM_WINDOWS
    typedef int socklen_t;
#endif
    sockaddr_in from;
    socklen_t from_len = sizeof(from);

    //recieve data from sendto function
    int bytes = recvfrom(handle, (char*) data, size, 0, (sockaddr*)&from, &from_len);
    

    if (bytes == SOCKET_ERROR) return 0;

    unsigned int from_address = 
            ntohl( from.sin_addr.s_addr );

    unsigned int from_port = 
        ntohs( from.sin_port );

    printf("we got message from port: %d and address: %d", from_port, from_address);
    
    return bytes;
}
