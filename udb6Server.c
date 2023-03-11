#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char **argv){
    if(argc != 2){
        printf("Usage: %s <port>\n", argv[0]);
        exit(0);
    }

    int port = atoi(argv[1]);
    int sockfd;
    struct sockaddr_in6 si_me, si_other;
    char buffer[1024];
    socklen_t addr_size;

    sockfd = socket(AF_INET6, SOCK_DGRAM, 0);

    memset(&si_me, '\0', sizeof(si_me));
    si_me.sin6_family = AF_INET6;
    si_me.sin6_port = htons(port);
    si_me.sin6_addr = in6addr_any;

    bind(sockfd, (struct sockaddr*)&si_me, sizeof(si_me));

    while(1) {
        addr_size = sizeof(si_other);
        memset(buffer, '\0', sizeof(buffer));
        recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr*)& si_other, &addr_size);
        char ip_str[INET6_ADDRSTRLEN];
        inet_ntop( AF_INET6, &si_other.sin6_addr, ip_str, INET6_ADDRSTRLEN);
        printf("[+] Data Received from %s:%d: %s", ip_str, ntohs(si_other.sin6_port), buffer);
    }

    return 0;
}
