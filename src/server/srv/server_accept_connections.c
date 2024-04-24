/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** server_accept_connections
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

void accept_connections(int server_fd, client_fds_t *client_fds,
    int *max_clients)
{
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    int new_socket = accept(server_fd, (struct sockaddr *)&address,
    (socklen_t *)&addrlen);

    if (new_socket < 0) {
        printf("accept");
        exit(EXIT_ERROR_EPITECH);
    }
    printf("New connection  %s:%d\n", inet_ntoa(address.sin_addr),
    ntohs(address.sin_port));
    if (*max_clients < MAX_CLIENTS) {
        client_fds[*max_clients].server_fd = new_socket;
        (*max_clients)++;
    } else {
        printf("Too many connections, rejecting...\n");
        close(new_socket);
    }
}
