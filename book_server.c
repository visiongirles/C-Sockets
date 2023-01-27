#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>


#define SERVER_PORT 8080
#define SERVER_ADDRESS AF_LOCAL
#define SOCKET_TYPE SOCK_STREAM
#define DOMAIN AF_INET
#define BACKLOG 10 // how many pending connections queue will hol

int main(int argc, char const* argv[]) {  

    int status;
    struct addrinfo hints; // address info
    struct addrinfo *servinfo; // to store results
    struct sockaddr_storage their_addr;
    socklen_t addr_size;
    int server_fd, new_socket, valread; 
    int opt = 1;
    // char buffer[1024] = { 0 };
    // char* hello = "Hello from server";


    memset(&hints, 0, sizeof hints); // make sure struct if empty -> fills it with zeros
    hints.ai_family = AF_UNSPEC; // don't care IPv4 or IPv6
    hints.ai_socktype = SOCKET_TYPE; // TCP/IP socket
    hints.ai_flags = AI_PASSIVE; // entended to bind
    hints.ai_addr = SERVER_ADDRESS;
    hints.ai_addrlen = sizeof(SERVER_ADDRESS);
    // if (status = getaddrinfo(SERVER_ADDRESS, SERVER_PORT, &hints, &servinfo) != 0) {
    //     fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
    //     return 2;
    // }

    // printf("ai_flags: %d, ai_family: %d, ai_socktype: %d, ai_protocol: %d, ai_canonname: %s\n", 
    // servinfo->ai_flags, servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol, servinfo->ai_canonname);



// struct addrinfo
// {
//   int ai_flags;			/* Input flags.  */
//   int ai_family;		/* Protocol family for socket.  */
//   int ai_socktype;		/* Socket type.  */
//   int ai_protocol;		/* Protocol for socket.  */
//   socklen_t ai_addrlen;		/* Length of socket address.  */
//   struct sockaddr *ai_addr;	/* Socket address for socket.  */
//   char *ai_canonname;		/* Canonical name for service location.  */
//   struct addrinfo *ai_next;	/* Pointer to next in list.  */
// };




// create a socket
// -1 if error
    if ((server_fd = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    // printf("%d\n", server_fd);

 // Forcefully attaching socket to the port 8080 - avoid "address already in use" error
    if (setsockopt(server_fd, SOL_SOCKET,
                   SO_REUSEADDR | SO_REUSEPORT, &opt,
                   sizeof(opt))) {
        perror("setsockopt failed");
        exit(EXIT_FAILURE);
    }

    // address.sin_family = DOMAIN;
    // address.sin_addr.s_addr = INADDR_ANY;
    // address.sin_port = htons(PORT);

    if (bind(server_fd, servinfo->ai_addr, servinfo->ai_addrlen) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, BACKLOG) < 0) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }

    addr_size = sizeof their_addr;
    if (new_socket = accept(server_fd, (struct sockaddr*)&their_addr, &addr_size) < 0) {
        perror("connect failed");
        exit(EXIT_FAILURE);
    }

    freeaddrinfo(servinfo);

    return 0;
}