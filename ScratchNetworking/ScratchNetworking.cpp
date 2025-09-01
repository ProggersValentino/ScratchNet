


#include "Client.h"
#include "NetworkSocket.h"
#include "Server.h"
#include "Socket.h"

int main(int argc, char* argv[])
{
    NetworkSocket *socketPack = new NetworkSocket();

    socketPack->InitializeSockets();

    std::cout << "initialized sockets" << std::endl;

    int type;
    unsigned short selectedport;

    std::cout << "are we a server or client?" << std::endl;
    std::cin >> type;

    std::cout << "which port are we listening to?" << std::endl;
    std::cin >> selectedport;

    std::cin.ignore();
    
    if (type == 1) //server set up
    {
        Server server;
        server.init_server(selectedport);

        server.ServerProcess();
    }
    else if (type == 2) //client setup
    {
        Client client;

        client.InitClient(selectedport, argv[1]);

        client.ClientProcess();
    }

    WSACleanup();

    return 0;
    
}
