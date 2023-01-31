// by duckate, Kate Sychenko

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define SIZE 1024
#define SERVER_PORT 8080
#define BACKLOG 10 // how many pending connections queue will hold

int main(int argc, char const* argv[]) {  

    struct sockaddr_in address;
    int server_fd, new_socket, valread; 
    char buffer[1024] = { 0 };
    char* hello = "Hello from server\n";
    int addrlen = sizeof(address);
    
    // create a socket
    // -1 if error
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("[-] SERVER: socket creation failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(SERVER_PORT);
    int yes = 1;

    // get rid of "Address already in use" error
    if ((setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes))) < 0) {
        perror("[-] SERVER: setsockopt failed");
        exit(EXIT_FAILURE);
    }

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("[-] SERVER: bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, BACKLOG) < 0) {
        perror("[-] SERVER:: listen failed");
        exit(EXIT_FAILURE);
    }

    while (1) {    
        if ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
            perror("[-] SERVER: accept failed");
            exit(EXIT_FAILURE);
        }

    read(new_socket, buffer, SIZE);
    printf("[+] CLIENT SAYS: %s", buffer);

    char response[] = "HTTP/1.1 200 OK\r\n\n\r<!DOCTYPE html><html>\n\r<body>\n\r<h1>Kate is here</h1><p>Typing from the server.</p></body></html>";

    send(new_socket, response, strlen(response), 0);
    printf("[+] SERVER: Package is sent\n");

    // find out client's address and port
    socklen_t len;
    struct sockaddr_storage addr;
    char ipstr[INET6_ADDRSTRLEN];
    int port;
    len = sizeof addr;

    getpeername(new_socket, (struct sockaddr*)&addr, &len);
     // deal with both IPv4 and IPv6:
    if (addr.ss_family == AF_INET) {
        struct sockaddr_in *s = (struct sockaddr_in *)&addr;
        port = ntohs(s->sin_port);
        inet_ntop(AF_INET, &s->sin_addr, ipstr, sizeof ipstr);
    } else { // AF_INET6
        struct sockaddr_in6 *s = (struct sockaddr_in6 *)&addr;
        port = ntohs(s->sin6_port);
        inet_ntop(AF_INET6, &s->sin6_addr, ipstr, sizeof ipstr);
    }

    printf("[+] Peer IP address: %s\n", ipstr);
    printf("[+] Peer port : %d\n", port);

    // closing the connect socket
    close(new_socket);
    }
    // closing the listening socket
    close(server_fd);

    // int status;
    // status = shutdown(server_fd, SHUT_RDWR);

    return 0;
}