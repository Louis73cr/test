/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** server
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
#include <signal.h>

void set_values(client_fds_t *client_fds)
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        client_fds[i].server_fd = 0;
        client_fds[i].is_connected = NOT_CONNECTED;
        client_fds[i].client_uuid = 0;
    }
}

void max_file_descriptor_check(int *max_fd, int server_fd)
{
    if (server_fd > *max_fd)
        *max_fd = server_fd;
}

void server_loop(int server_fd, client_fds_t *client_fds, int *max_clients,
    data_t *data_server)
{
    fd_set readfds;
    int max_fd = server_fd;

    FD_ZERO(&readfds);
    FD_SET(server_fd, &readfds);
    for (int i = 0; i < *max_clients; i++) {
        if (client_fds[i].server_fd > 0) {
            FD_SET(client_fds[i].server_fd, &readfds);
            max_file_descriptor_check(&max_fd, client_fds[i].server_fd);
        }
    }
    if (select(max_fd + 1, &readfds, NULL, NULL, NULL) < 0) {
        printf("select error");
        exit(EXIT_ERROR_EPITECH);
    }
    if (FD_ISSET(server_fd, &readfds))
        accept_connections(server_fd, client_fds, max_clients);
    check_client_data(client_fds, *max_clients, data_server);
    save_client_data(data_server);
}

void quit_srv(int signum, client_fds_t *client_fds)
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (client_fds[i].server_fd != 0 && signum == SIGINT) {
            dprintf(client_fds[i].server_fd, "555 end of services\n");
            close(client_fds[i].server_fd);
        }
    }
    exit(0);
}

void server_launch(char *port)
{
    int server_fd;
    client_fds_t client_fds[MAX_CLIENTS];
    int max_clients = 0;
    data_t data_server;
    struct sigaction sig;

    sig.sa_handler = (void (*)(int))quit_srv;
    sigemptyset(&sig.sa_mask);
    sig.sa_flags = 0;
    sig.sa_flags |= SA_SIGINFO;
    sig.sa_sigaction = (void (*)(int, siginfo_t *, void *))quit_srv;
    sigaction(SIGINT, &sig, NULL);
    load_client_data(&data_server);
    set_values(client_fds);
    server_fd = create_server_socket(atoi(port));
    while (1)
        server_loop(server_fd, client_fds, &max_clients, &data_server);
    close(server_fd);
    free(data_server.users);
    free(data_server.teams);
}
