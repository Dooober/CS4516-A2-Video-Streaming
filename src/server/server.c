#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>

#include "server_worker.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: server [PORT]\n");
        return -1;
    }
    int port = atoi(argv[1]);

    int rtsp_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (rtsp_sockfd < 0) {
        printf("Socket creation failed: %s\n", strerror(errno));
        return -1;
    }

    struct sockaddr_in address;
    socklen_t addrlen = sizeof(address);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(rtsp_sockfd, (struct sockaddr*) &address, sizeof(address)) < 0) {
        printf("Socket bind failed: %s\n", strerror(errno));
        return -1;
    }

    if (listen(rtsp_sockfd, 5) < 0) {
        printf("Socket failed to listen: %s\n", strerror(errno));
        return -1;
    }

    // Receive client info (address, port) through RTSP/TCP session
    while (1) {
        struct client_info info;
        info.sockfd = accept(rtsp_sockfd, (struct sockaddr*) &address, &addrlen);
        if (info.sockfd >= 0) {
            printf("Client connected\n");
            server_worker_run(&info);
        }
    }

    //close(rtsp_sockfd);

    return 0;
}

