#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define MAX 1024
#define PORT 8080

void perform_connection(int connected_fd) {
    char buff[MAX];
    int n;

    for (;;) {
        bzero(buff, MAX);

        read(connected_fd, buff, sizeof(buff));
        printf("From client: %s\t To client : ", buff);

        bzero(buff, MAX);
        n = 0;
        while((buff[n++] = getchar()) != '\n') {
            write(connected_fd, buff, sizeof(buff));

            if (strncmp("exit", buff, 4) == 0) {
            printf("Server Exit...\n");
            break;
            }
        }
    }
}

int main() {
    int server_fd, connect_fd;
    struct sockaddr_in serv_info;

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("SERVER: socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&serv_info, 0, sizeof(serv_info));
    serv_info.sin_addr = INADDR_ANY;
    serv_info.sin_family = AF_INET;
    serv_info.sin_port = htons(PORT); // “Host to Network Short”

// htons() host to network short
// htonl() host to network long
// ntohs() network to host short
// ntohl() network to host long




    if ((bind(server_fd, )) < 0)



    return 0;
}