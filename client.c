#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8080


int main(int argc, char const* argv[]) {  
    
    struct sockaddr_in serv_addr;
    int client_fd = 0, status, valread; 
    char buffer[1024] = { 0 };
    char* hello = "Hello from client\n";

// create a socket
// -1 if error
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("CLIENT: socket creation failed");
        exit(EXIT_FAILURE);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = INADDR_ANY;

//  if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)
//         <= 0) {
//         perror(
//             "\nInvalid address/ Address not supported \n");
//         exit(EXIT_FAILURE);
//     }

    
    if ((status
         = connect(client_fd, (struct sockaddr*)&serv_addr,
                   sizeof(serv_addr)))
        < 0) {
        perror("CLIENT: Connection Failed\n");
        exit(EXIT_FAILURE);
    }

    send(client_fd, hello, strlen(hello), 0);
    printf("CLIENT: Hello message sent\n");
    valread = read(client_fd, buffer, 1024);
    printf("CLIENT BUFFER: %s\n", buffer);
 
printf("client_fd value    = %d\n", client_fd);


    // closing the connected socket
    close(client_fd);

    return 0;
}