#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>

struct ConnectionInfo {
    int newSocket;
    struct sockaddr_in newAddr;
};

void *handle_connection(void *arg);

int main(int argc, char **argv){
    if(argc != 3){
        printf("Usage: %s <port> <max_connections>\n", argv[0]);
        exit(0);
    }

    int port = atoi(argv[1]);
    int max_connections = atoi(argv[2]);

    int sockfd;
    struct sockaddr_in serverAddr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    memset(&serverAddr, '\0', sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = INADDR_ANY; // allow connections from any address

    bind(sockfd, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
    printf("[+]Bind to Port number %d.\n", port);

    listen(sockfd, max_connections);
    printf("[+]Listening...\n");

    pthread_t threads[max_connections];
    int i = 0;

    while(1){
        struct sockaddr_in newAddr;
        socklen_t addr_size = sizeof(newAddr);
        int newSocket = accept(sockfd, (struct sockaddr *) &newAddr, &addr_size);

        printf("[+]Accepted a new connection from %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));

        struct ConnectionInfo *info = malloc(sizeof(struct ConnectionInfo));
        info->newSocket = newSocket;
        info->newAddr = newAddr;

        pthread_create(&threads[i], NULL, handle_connection, (void *) info);
        i++;
    }

    return 0;
}

void *handle_connection(void *arg){
    struct ConnectionInfo *info = (struct ConnectionInfo *) arg;
    int newSocket = info->newSocket;
    struct sockaddr_in newAddr = info->newAddr;

    char buffer[2048];

    strcpy(buffer, "Successfully connected to the server.\n");
    send(newSocket, buffer, strlen(buffer), 0);
    memset(buffer, 0, sizeof(buffer));

    while(recv(newSocket, buffer, 1024, 0) > 0){
        printf("Received: %s from %s:%d\n", buffer, inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));
        strcpy(buffer, "Server received message.\n");
        send(newSocket, buffer, strlen(buffer), 0);
        memset(buffer, 0, sizeof(buffer));
    }

    printf("[+]Closing the connection.\n");
    close(newSocket);

    pthread_exit(NULL);
}
