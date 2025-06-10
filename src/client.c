#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h> // For inet_addr()
#define PORT 8000
#define MAX 80

void chatWithServer(int sockfd){
    char buffer[MAX];
    int n;

    while(1){
        // first empty prev message or garbage value
        bzero(buffer, sizeof(buffer));

        // read messgae from the server
        printf("Enter message to server: ");
        n = 0;
        while ((buffer[n++] = getchar()) != '\n');
        // do{
        //     buffer[n++] = getchar();
        // }while(buffer[n - 1] != '\n');

        // Send message to the server
        write(sockfd,buffer,sizeof(buffer));

        if(strncmp("exit", buffer, 4) == 0){
            printf("Server Exited...\n"); 
            close(sockfd);
            break; 
        }

        bzero(buffer, sizeof(buffer));          // to reset the buffer every time

        read(sockfd,buffer,sizeof(buffer));
        printf("From Server: %s", buffer);

        if(strncmp("exit", buffer, 4) == 0){
            printf("Server Exited...\n"); 
            close(sockfd);
            break; 
        }
    }
}

void main(){
    int sockfd;
    struct sockaddr_in serverAddress, client_address;

    sockfd = socket(AF_INET,SOCK_STREAM,0);     // connecting to the socket

    if (sockfd == -1){      // Returns a file descriptor for the new socket, or -1 for errors.
        printf("Client socket creation failed...\n");
        exit(0);                // end execution
    }else{
        printf("Client Socket successfully created..\n");
    }

    bzero(&serverAddress,sizeof(serverAddress));

    // Assign IP and port
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");        // Connect to localhost
    serverAddress.sin_port = htons(PORT);

    if(connect(sockfd,(struct sockaddr*)&serverAddress,sizeof(serverAddress))){      // we are trying to connect to the server
        printf("Connection with the server failed...\n");       
        exit(0);
    } else {
        printf("Connected to the server...\n");
    }

    chatWithServer(sockfd);

    close(sockfd);
}