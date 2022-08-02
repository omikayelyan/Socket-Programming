#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
    int server;
    int client;
    const int bufSize = 1024;
    char buffer[bufSize];
    // All ports bellow 1024 are reserved for standard services.
    int portNumber = 1800;
    bool isExit = false;

    // This structure is defined in <netinet/in.h>, and it contains an internet address.
    struct sockaddr_in server_address; 
    socklen_t size; // unsigned integral type of length of at least 32 bits.

    // socket() creates an endpoint for communication and returns a file descriptor.
    client = socket(AF_INET, SOCK_STREAM, 0); 
    // AF_INET on different hosts, SOCK_STREAM TCP(Transmission Control Protocol)
    if (client < 0)
    {
        std::cout << "Can't connect." << std::endl;
        exit(1); // EXIT_FAILURE, unsuccessful termination
    }
    std::cout << "\nSocket server has been created." << std::endl;

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htons(INADDR_ANY); // Any address for binding. 
    // htons() function translates a short integer from host byte order to network byte order.
    server_address.sin_port = htons(portNumber);

    // The bind() function binds a unique local name to the socket with descriptor socket. 
    if((bind(client, (struct sockaddr*)&server_address, sizeof(server_address))) < 0)
    {
        std::cout << "Can't bind connection." << std::endl;
        exit(1);
    }

    size = sizeof(server_address);
    std::cout << "Waiting for a client.." << std::endl;

    // Listen() for connections on a socket, it puts the server socket in a passive mode,
    // where it waits for the client to approach the server to make a connection. 
    listen(client, 1); 
    // Accept() call is used by a server to accept a connection request from a client. 
    server = accept(client, (struct sockaddr *)&server_address, &size);

    if (server < 0)
    {
        std::cout << "Error on accepting!" << std::endl;
    }

    while (server > 0)
    {
        strcpy(buffer, "Server connected.\n");
        // The send() function shall send a message only when the socket is connected.
        send(server, buffer, bufSize, 0);
        std::cout << "Connected with the client." << std::endl;
        std::cout << "For end of the line, enter . symbol." << std::endl;
        std::cout << "If you want to end the connection, enter ^ symbol." << std::endl;

        std::cout << "Client: ";
        do 
        {
            // Receive message from specified socket into specified buffer.
            recv(server, buffer, bufSize, 0);
            std::cout << buffer << " ";
            if (*buffer == '^')
            {
                *buffer = '.';
                isExit = true;
            }
        } while (*buffer != '.');

        do
        {
            std::cout << "\nServer: ";
            do
            {
                std::cin >> buffer;
                // Send specified message using specified socket.
                send(server, buffer, bufSize, 0);
                if (*buffer == '^')
                {
                    send(server, buffer, bufSize, 0);
                    *buffer = '.';
                    isExit = true;
                }
            } while (*buffer != '.');

            std::cout << "Client: ";
            do
            {
                recv(server, buffer, bufSize, 0);
                std::cout << buffer << " ";
                if (*buffer == '^')
                {
                    *buffer = '.';
                    isExit = true;
                }
            } while (*buffer != '.');
        } while (!isExit);

        // inet_ntoa converts packet data to IP, which was taken from client.
        std::cout << std:: endl << "\nConnection terminated with IP: " << inet_ntoa(server_address.sin_addr);
        close(server);
        isExit = false;
        exit(1);
    }
    close(client);
}
