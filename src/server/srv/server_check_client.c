/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** server_check_client
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

void check_buffer(client_fds_t *client_fds, data_t *data_server,
    int client_socket)
{
    char buffer[BUF_SIZE];
    int valread;

    valread = read(client_socket, buffer, BUF_SIZE);
    if (valread == 0) {
        printf("Client disconnected\n");
        close(client_socket);
        client_fds->server_fd = 0;
        return;
    }
    buffer[valread] = '\0';
    if (strstr(buffer, "\n") != NULL) {
        buffer[valread - 2] = '\0';
        handle_message(buffer, client_fds, data_server);
        buffer[0] = '\0';
    }
}

void delete_client(int i, client_fds_t *client_fds)
{
    for (int j = i; j < MAX_CLIENTS - 1; j++)
        client_fds[j] = client_fds[j + 1];
}

void check_logout_client(client_fds_t *client_fds)
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (client_fds[i].client_uuid == 0) {
            delete_client(i, client_fds);
        }
    }
}

void read_socket(int max_clients, client_fds_t *client_fds, fd_set readfds,
    data_t *data_server)
{
    int client_socket;

    for (int i = 0; i < max_clients; i++) {
        client_socket = client_fds[i].server_fd;
        if (client_socket > 0 && FD_ISSET(client_socket, &readfds)) {
            check_buffer(&client_fds[i], data_server, client_socket);
        }
    }
    check_logout_client(client_fds);
}

void check_client_data(client_fds_t *client_fds, int max_clients,
    data_t *data_server)
{
    fd_set readfds;
    int max_fd = -1;

    FD_ZERO(&readfds);
    for (int i = 0; i < max_clients; i++) {
        if (client_fds[i].server_fd > 0) {
            FD_SET(client_fds[i].server_fd, &readfds);
            max_file_descriptor_check(&max_fd, client_fds[i].server_fd);
        }
    }
    if (select(max_fd + 1, &readfds, NULL, NULL, NULL) < 0) {
        printf("select error");
        exit(EXIT_ERROR_EPITECH);
    }
    read_socket(max_clients, client_fds, readfds, data_server);
}
