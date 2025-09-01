


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


    /*const int sendport = 30000;
    const int recvport = 30001;

    Socket socketSender;

    if (!socketSender.OpenUDPServSock(sendport))
    {
        printf("failed to open socket\n");
        return -1;
    }
    std::cout << "created a socket" << std::endl;
    
    Socket socketListener;

    if (!socketListener.OpenUDPServSock(recvport))
    {
        printf("failed to open socket\n");
        return -1;
    }

    std::cout << "created a socket" << std::endl;

    //send packets
    const char data[] = "hello world!";
    socketSender.Send(Address(127,0,0,1,recvport), data, sizeof(data));
    
    std::cout << "sent packets" << std::endl;

    int bytes_read;
    
    //retrieve packets from sender
    while (true)
    {
        Address sender;
        unsigned char buffer[256];
        bytes_read = socketListener.Receive(sender, buffer, sizeof(buffer));

        if (!bytes_read) continue;

        buffer[bytes_read] = '\0'; // null terminate
        printf("received bytes from socket: %d\n", bytes_read);
    }*/
    
}
