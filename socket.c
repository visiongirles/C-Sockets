#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>


#define PORT 8080

int main(int argc, char const* argv[]) {  

    int status;
    struct addrinfo hints; // address info
    struct addrinfo *servinfo; // to store results



    memset(&hints, 0, sizeof hints); // make sure struct if empty -> fills it with zeros
    hints.ai_family = AF_UNSPEC; // don't care IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM; // TCP/IP socket
    hints.ai_flags = AI_PASSIVE; // entended to bind

    if (status = getaddrinfo("www.example.net", "3490", &hints, &servinfo) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
        return 2;
    }


 

    printf("ai_flags: %d, ai_family: %d, ai_socktype: %d, ai_protocol: %d, ai_canonname: %s\n", 
    servinfo->ai_flags, servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol, servinfo->ai_canonname);
    freeaddrinfo(servinfo);



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


    int server_fd, new_socket, valread; 
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = { 0 };
    char* hello = "Hello from server";

// create a socket
// -1 if error
    if (server_fd = socket(PF_INET, SOCK_SEQPACKET, 0) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }


    return 0;
}