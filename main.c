#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

#define IP "192.168.1.68"

int main() {
    int status;
    struct addrinfo hints;
    struct addrinfo *res;

    memset(&hints, 0, sizeof hints);

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    getaddrinfo(IP, "8088", &hints, &res);

    int socket_fd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    connect(socket_fd, res->ai_addr, res->ai_addrlen);

    while (1) {
        char msg[64];
        char ans[64] = {0,};

        printf("Enter message: ");
        scanf("%s", msg);

        send(socket_fd, msg, strlen(msg), 0);
        recv(socket_fd, ans, 64, 0);
        printf("Server: %s\n", ans);

        if (strcmp(msg, "exit") == 0) {
            break;
        }
    }
    freeaddrinfo(res);
    close(socket_fd);
    return 0;
}