#pragma once
#include <iostream>
#include <winsock2.h>
#pragma comment (lib, "ws2_32.lib") /*creating a link to the winsock library to get socket functionality by telling the linker*/

#include "NetworkSocket.h"

//platfrom detection
#define PLATFORM_WINDOWS  1
#define PLATFORM_MAC      2
#define PLATFORM_UNIX     3

#if defined(WIN32)
#define PLATFORM PLATFORM_WINDOWS
#elif defined(__APPLE__)
#define PLATFORM PLATFORM_MAC
#else
#define PLATFORM PLATFORM_UNIX
#endif

/*including the appropriate libraries for each OS */
#if PLATFORM == PLATFORM_WINDOWS

 
#elif PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_UNIX

#endif


class NetworkSocket
{
public:
    /*activate the socket layer -> this is required for winsock2 to work */
    bool InitializeSockets();

    /*shuts down all sockets no matter how many threads are across it*/
    void ShutdownSockets();
};
