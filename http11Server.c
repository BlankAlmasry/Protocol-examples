#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BUF_SIZE 1024

int main(int argc, char *argv[]) {
    int port, max_connections;
    if (argc < 3) {
        printf("Usage: %s <port>\n <max_connections>", argv[0]);
        return 1;
    } else {
        port = atoi(argv[1]);
        max_connections = atoi(argv[2]);
    }

    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    char buffer[BUF_SIZE];

    // Create a TCP/IP socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Error creating socket\n");
        return 1;
    }

    // Bind the socket to a specific address and port
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error binding socket\n");
        return 1;
    }

    if (listen(server_socket, max_connections) < 0) {
        perror("Error listening on socket\n");
        return 1;
    }

    printf("Serving on port %d...\n", port);

    while (1) {
        printf("Waiting for a connection...\n");
        // Wait for a connection
        socklen_t client_size = sizeof(client_addr);
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_size);
        if (client_socket < 0) {
            printf("Error accepting connection\n");
            continue;
        }

        // Read the request from the client
        memset(buffer, 0, BUF_SIZE);
        int bytes_read = read(client_socket, buffer, BUF_SIZE);
        if (bytes_read < 0) {
            printf("Error reading request\n");
            close(client_socket);
            continue;
        }

        // Print the request
        printf("Request:\n%s\n", buffer);

        // Send a response
        char response[] = "HTTP/1.1 200 OK\r\nContent-Length: 13\r\n\r\nHello, world!";
        int bytes_written = write(client_socket, response, strlen(response));
        if (bytes_written < 0) {
            printf("Error sending response\n");
        }


        // Close the connection
        close(client_socket);
    }

    // Close the server socket
    close(server_socket);
    return 0;
}
