#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // read(), write(), close()
#define PORT 8000
#define MAX 80 
#define SA struct sockaddr

void chatWithClient(int connfd){
    char buffer[MAX];   // MAX = 80
    int n;

    while(1){
        bzero(buffer, MAX);

        // read the message from the client in buffer format
        read(connfd,buffer,sizeof(buffer));
        printf("Buffer from the client - %s\n",buffer);

        // Check if client want to exit
        if(strncmp("exit", buffer, 4) == 0){
            printf("Client wants to Exit...\n"); 
            close(connfd);
            break; 
        }
        n = 0;
        
        bzero(buffer, MAX);        

        // copy server message in the buffer 
        printf("Enter message for the client: ");
        do{
            buffer[n++] = getchar();
        }while(buffer[n - 1] != '\n');

        // and send that buffer to client 
        write(connfd,buffer,sizeof(buffer));

        // The function call strncmp("exit", buffer, 4) compares the first 4 characters of the string "exit" with the first 4 characters of the string stored in the variable buffer
        if (strncmp("exit", buffer, 4) == 0) {
            printf("Server Exit...\n");
            close(connfd);
            break;
        }
    }       
}

void main()
{
    // sockfd: An integer representing the socket file descriptor, returned by socket().
    // connfd: A placeholder to store the connection file descriptor when a client connects (not yet used in this code).
    // len: Will store the size of the client's address structure (not yet used).
    int sockfd, connfd, len;

    // serverAddress: A structure to store the server's IP address and port.
    // cli: A structure to store the client's address when a connection is established.
    struct sockaddr_in serverAddress, client_address;

    // Purpose: Creates a socket for communication.
    // Parameters:
    //     AF_INET: Specifies the address family for IPv4.
    //     SOCK_STREAM: Specifies a reliable, connection-oriented TCP protocol.
    //     0: Uses the default protocol for SOCK_STREAM (TCP).
    // Returns: A non-negative integer (socket descriptor) on success, or -1 on failure.
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    printf("AF_INET - %d \nSOCK_STREAM - %d \nsockfd - %d \nSize of serverAdress - %ld\n", sockfd, AF_INET, SOCK_STREAM, sizeof(serverAddress));
    
    if (sockfd == -1){      // Returns a file descriptor for the new socket, or -1 for errors.
        printf("socket creation failed...\n");
        exit(0);                // end execution
    }else{
        printf("Socket successfully created..\n");
    }

    // Purpose: Sets all bytes of serverAddress to 0.
    // Reason: Ensures no garbage values are present in the structure before filling it.
    bzero(&serverAddress, sizeof(serverAddress));

    // assign ip,port
    // AF_INET indicates ipv4 addressing so it mentions that the socket will use ipv4 protocol
    serverAddress.sin_family = AF_INET;
    // INADDR_ANY: A macro that resolves to 0.0.0.0. It tells the system to bind to all available network interfaces on the host machine.
    // htonl: Converts the IP address from host byte order to network byte order.
    // Usage: Allows the server to accept connections from any IP address.
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    // Purpose: Assigns the port number to the server.
    serverAddress.sin_port = htons(PORT);

    // serverAddress.sin_family = 2;           // AF_INET (IPv4)
    // serverAddress.sin_addr.s_addr = 0;     // INADDR_ANY (0.0.0.0 in network byte order)
    // serverAddress.sin_port = 0x1f40;       // 8000 in network byte order (hexadecimal representation)

    if (bind(sockfd, (SA *)&serverAddress, sizeof(serverAddress)) != 0){
        printf("Socket Bind Failed..\n");
        exit(0); // exits from main and execution is over
    }
    else    {
        printf("Socket successfully binded....\n");
    }

    if(listen(sockfd, 5) == -1){
        printf("Listen failed...\n"); 
        exit(0); 
    } 
    else
        printf("Server listening..\n"); 

    len = sizeof(client_address);
    // accept data packet from the client and verification
    connfd = accept(sockfd, (SA*)(&client_address), &len);     
    // (SA*)&cli - Casts the address of 'cli' (struct sockaddr_in*) to a generic socket address type (struct sockaddr*) for compatibility with accept()
    if (connfd < 0){
        printf("Server accept failed...\n");
        exit(0);
    }
    else
        printf("server accept the client...\n");

    chatWithClient(connfd);         // server hello and client hello

    close(sockfd);
}