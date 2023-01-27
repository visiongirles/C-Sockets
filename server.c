#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>


#define SERVER_PORT 8080
#define BACKLOG 10 // how many pending connections queue will hol

int main(int argc, char const* argv[]) {  

    struct sockaddr_in address, test;
    int server_fd, new_socket, valread; 
    char buffer[1024] = { 0 };
    char* hello = "Hello from server\n";
    int addrlen = sizeof(address);
    
// create a socket
// -1 if error
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("SERVER: socket creation failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_LOCAL;
    address.sin_addr.s_addr = INADDR_LOOPBACK;
    address.sin_port = htons(SERVER_PORT);

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("SERVER: bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, BACKLOG) < 0) {
        perror("SERVER: listen failed");
        exit(EXIT_FAILURE);
    }

    if ((new_socket = accept(
        server_fd, 
    (struct sockaddr*)&address, 
    (socklen_t*)&addrlen
    )) < 0) {
        perror("SERVER: accept failed");
        exit(EXIT_FAILURE);
    }


//TODO: РАЗОБРАТЬ 
    valread = read(new_socket, buffer, 1024);
    printf("SERVER BUFFER: %s\n", buffer);
    send(new_socket, hello, strlen(hello), 0);
    printf("SERVER: Hello message sent\n");

    getsockname(new_socket, (struct sockaddr *)&test, (socklen_t*)sizeof(test));
    printf("address: %d, port: %d\n", test.sin_addr.s_addr, test.sin_port);
    printf("server_fd: %d\n", server_fd);
    printf("new_socket: %d\n", new_socket);


    read(STDIN_FILENO, buffer, 10);

    // closing the connectesocket
    close(new_socket);
    // closing the listening socket

    int status;
    status = shutdown(server_fd, SHUT_RDWR);

    return 0;
}