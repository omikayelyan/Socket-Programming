#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdlib>
#include <unistd.h>
#include <netdb.h>

int main()
{
    int client;
    int portNumber = 1800; 
    int bufSize = 1024;
    char buffer[bufSize];
    bool isExit = false;
    const char* ip = "127.0.0.1";

    struct sockaddr_in server_address;
    /* struct sockaddr_in {
    short            sin_family;   
    unsigned short   sin_port;     
    struct in_addr   sin_addr;     
    char             sin_zero[8];  
    };

    struct in_addr {
    unsigned long s_addr;
    }; */

    client = socket(AF_INET, SOCK_STREAM, 0);
    if (client < 0)
    {
        std::cout << "\nCan't connect." << std::endl;
        exit(1);
    }
    std::cout << "\nSocket client has been created." << std::endl;

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(portNumber);
    
    // The connect() call on a stream socket is used by the client application to establish a connection to a server. 
    if (connect(client, (struct sockaddr *)&server_address, sizeof(server_address)) == 0)
    {
        std::cout << "Connection to the server port number: " << portNumber << std::endl;
    }
    std::cout << "Waiting for the server.." << std::endl; 
    recv(client, buffer, bufSize, 0);
    std::cout << "Connection confirmed." << std::endl;

    std::cout << "For end of the line, enter . symbol.";
    std::cout << "\nIf you want to end the connection, enter ^ symbol." << std::endl;

    do
    {
        std::cout << "Client: ";
        do
        {
            std::cin >> buffer;
            send(client, buffer, bufSize, 0);
            if (*buffer == '^')
            {
                send(client, buffer, bufSize, 0);
                *buffer = '.';
                isExit = true;
            }
        } while (*buffer != '.');

        std::cout << "Server: ";
        do
        {
            recv(client, buffer, bufSize, 0);
            std::cout << buffer << " ";
            if (*buffer == '^')
            {
                *buffer = '.';
                isExit = true;
            }
        } while (*buffer != '.');
        std::cout << std::endl;
        
        
    } while (!isExit);
    
    std::cout << "\nConnection terminated.";
    close(client);
}