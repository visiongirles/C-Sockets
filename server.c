#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define SIZE 1024
#define SERVER_PORT 8080
#define BACKLOG 10 // how many pending connections queue will hol


// void send_file(FILE *fp, int sockfd){
//   int n;
//   char data[SIZE] = {0};
 
//   while(fgets(data, SIZE, fp) != NULL) {
//     if (send(sockfd, data, sizeof(data), 0) == -1) {
//       perror("[-]Error in sending file.");
//       exit(EXIT_FAILURE);
//     }
//     bzero(data, SIZE);
//   }
// }

int main(int argc, char const* argv[]) {  

    struct sockaddr_in address;
    int server_fd, new_socket, valread; 
    char buffer[1024] = { 0 };
    char* hello = "Hello from server\n";
    // FILE *fp;
    // fp = fopen ("index.html", "w+");

    // int i;
    // // char fn[150];
    // char str[] = "<!DOCTYPE html><html><body><h1>Привет медвед</h1></body></html>\n";
    //     for (i = 0; str[i] != '\n'; i++) {
    //         /* write to file using fputc() function */
    //         fputc(str[i], fp);
    //     }
    // fclose (fp); 

    int addrlen = sizeof(address);
    
// create a socket
// -1 if error
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("SERVER: socket creation failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(SERVER_PORT);
    int yes = 1;

    // get rid of "Address already in use" error
    if ((setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes))) < 0) {
        perror("[-]setsockopt failed");
        exit(EXIT_FAILURE);
    }

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("SERVER: bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, BACKLOG) < 0) {
        perror("SERVER: listen failed");
        exit(EXIT_FAILURE);
    }

while (1) {    
    if ((new_socket = accept(
                            server_fd, 
                            (struct sockaddr*)&address, 
                            (socklen_t*)&addrlen
                            )
    ) < 0) {
        perror("SERVER: accept failed");
        exit(EXIT_FAILURE);
    }

    // char request[] = "HTTP/1.1 200 OK\r\n\r\n<html>\n\r<body>\n\r\rhello\n\r</body>\n</html>";
    char response[] = "HTTP/1.1 200 OK\r\n\n\r<!DOCTYPE html><html>\n\r<body>\n\r<h1>Kate is here</h1><p>Typing from the server.</p></body></html>";
    send(new_socket, response, strlen(response), 0);

    // recv(new_socket, buffer, strlen(buffer), 0);
    //     printf("%s", buffer);

    // recv(new_socket, buffer, strlen(buffer), 0);
    //     printf("%s", buffer);

    // send(new_socket, request, strlen(request), 0);



//TODO: РАЗОБРАТЬ 
    // valread = read(new_socket, buffer, 1024);
    // printf("SERVER BUFFER: %s\n", buffer);
    // send(new_socket, fp, strlen(fp), 0);
    // send(new_socket, hello, strlen(hello), 0);
    // send_file(fp, new_socket);
    printf("SERVER: Hello message sent\n");

    // getpeername(new_socket, (struct sockaddr *)&test, (socklen_t*)sizeof(test));
    
    // char remotename[50];
    // inet_ntop(AF_INET, &test, remotename, sizeof(remotename));
    // printf("%s\n", remotename);
    // printf("address: %d, port: %d\n", test.sin_addr.s_addr, test.sin_port);
    // printf("server_fd: %d\n", server_fd);
    // printf("new_socket: %d\n", new_socket);


    // read(STDIN_FILENO, buffer, 10);

    // closing the connectesocket
    close(new_socket);
    }
    // closing the listening socket

    // int status;
    // status = shutdown(server_fd, SHUT_RDWR);

    return 0;
}