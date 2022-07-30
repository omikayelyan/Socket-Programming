# Socket-Programming


Socket programming is a means of communicating data between two computers across a network. Connections can be made using either a connection-oriented protocol or a connectionless protocol. In our case, we will use TCP/IP which is a connection-oriented protocol.

![socket-programming](https://user-images.githubusercontent.com/104993462/181925276-29fb0061-70ec-4fa3-aa53-1c14bf0f4d65.png)

Listening for a Connection

• A server (program) runs on a specific computer and has a socket that is bound to a specific port. The server waits and listens to the socket for a client to make a connection request.
![Screen Shot 2022-07-30 at 20 13 31](https://user-images.githubusercontent.com/104993462/181925761-a3b9f76e-4f91-4a2d-838b-b3325532a5e8.png)

• If everything goes well, the server accepts the connection.
• Upon acceptance,the server gets a new socket bound to a different port.
– It needs a new socket so that it can continue to listen to the original socket for connection requests while serving the connected client.

 Server-Side Sockets
 
• Bind socket to IPaddress/port
int bind(int socket, struct sockaddr *addr, int addr_len)

• Mark the socket as accepting connections
int listen(int socket, int backlog)

• “Passive open” accepts connect
int accept(int socket, struct sockaddr *addr, int addr_len)
(returns a new socket to talk to the client)

Client-Side Sockets

• int connect(int socket, struct sockaddr *addr, int addr_len)
