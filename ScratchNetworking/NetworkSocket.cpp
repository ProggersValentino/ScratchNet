#include "NetworkSocket.h"
#include <winsock2.h>

bool NetworkSocket::InitializeSockets()
{
#if PLATFORM == PLATFORM_WINDOWS
    WSADATA wsaData;
    WORD versionRequested;
    DWORD bufferSize = 0;

    LPWSAPROTOCOL_INFO SelectedProtocol;
    int NumProtocols;
    
    versionRequested = MAKEWORD(2, 2); 
    bool error = WSAStartup(versionRequested, &wsaData) != NO_ERROR; /*return result of whether an error has occured or not */

    if (error)
    {
        int socketError = WSAGetLastError();
        printf("could not start socket: %d", socketError);
        return false;
    }
    else
    {
        //confirm that WINSOCK2 DLL supports the exact version requesting otherwise cleanup
        if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
        {
            WSACleanup();
            return false;
        }
    }

    // //call WSAEnumProtocols to figure out how big of a buffer we need, the first time is to check if the buffer size is too small 
    // NumProtocols = WSAEnumProtocols(NULL, NULL, &bufferSize);
    //
    // if ((NumProtocols != SOCKET_ERROR) && (WSAGetLastError() != WSAENOBUFS))
    // {
    //     WSACleanup();
    //     return false;
    // }
    //
    // //Allocate a buffer; call WESAEnumProtocols to get an array of WSAPROTOCOL_INFO structs
    // SelectedProtocol = (LPWSAPROTOCOL_INFO)malloc(sizeof(WSAPROTOCOL_INFO));
    //
    // if (SelectedProtocol == NULL)
    // {
    //     WSACleanup();
    //     return false;
    // }
    //
    // //allocate memory for protocol list and define what protocols to look for
    // int* protos = (int*)calloc(2, sizeof(int));
    //
    // protos[0] = IPPROTO_TCP;
    // protos[1] = IPPROTO_UDP;
    //
    // NumProtocols = WSAEnumProtocols(protos, SelectedProtocol, &bufferSize);
    //
    // //to prevent memory leaks we free the data from its memory allocation
    // free(protos); 
    // protos = NULL;
    //
    // free(SelectedProtocol);
    // SelectedProtocol = NULL;

    // if (NumProtocols == SOCKET_ERROR)
    // {
    //     WSACleanup();
    //     return false;
    // }

    return true;
#else
    return true;
#endif
    
}

void NetworkSocket::ShutdownSockets()
{
#if PLATFORM == PLATFORM_WINDOWS
    WSACleanup();
    #endif
    
}
