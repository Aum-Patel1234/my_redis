#include <cstdio>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 8000

int main() {
  int sock = socket(AF_INET, SOCK_STREAM, 0);
  if (-1 == sock) {
    perror("Error: Socket creation failed");
    return 1;
  }
  // specifying the address
  sockaddr_in serverAddress;
  std::memset(&serverAddress, 0,
              sizeof(serverAddress)); // set garbage values to 0 if any
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(PORT);
  serverAddress.sin_addr.s_addr = INADDR_ANY;
  std::cout << "Socket connection successfull at port - " << PORT << std::endl;

  // bind the socket
  if (-1 ==
      bind(sock, (struct sockaddr *)&serverAddress, sizeof(serverAddress))) {
    perror("Binding to the serverAddress failed!");
    close(sock);
    return 1;
  }

  // listening to assigned socket
  listen(sock, 5);

  int client_sock_fd = accept(sock, nullptr, nullptr);
  if (client_sock_fd == -1) {
    perror("Error: Accept failed");
    close(sock);
    return 1;
  }

  // recieve data
  char buffer[1024] = {0};
  recv(sock, buffer, sizeof(buffer), 0);
  std::cout << "Message from client - " << buffer << std::endl;

  // closing the socket
  close(sock);

  return 0;
}
