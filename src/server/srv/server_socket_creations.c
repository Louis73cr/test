/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** server_socket_creations
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/select.h>
#include "../include/server.h"
#include "../include/prototype.h"

void bind_socket(int server_fd, struct sockaddr_in *address)
{
    if (bind(server_fd, (struct sockaddr *)address, sizeof(*address)) < 0) {
        printf("bind failed");
        exit(EXIT_ERROR_EPITECH);
    }
}

void listen_socket(int server_fd, int port)
{
    if (listen(server_fd, 5) == -1) {
        printf("listen");
        exit(EXIT_ERROR_EPITECH);
    }
    printf("Server listening on port %d...\n", port);
}

int create_server_socket(int port)
{
    int server_fd;
    struct sockaddr_in address;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        printf("socket failed");
        exit(EXIT_ERROR_EPITECH);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);
    bind_socket(server_fd, &address);
    listen_socket(server_fd, port);
    return server_fd;
}
