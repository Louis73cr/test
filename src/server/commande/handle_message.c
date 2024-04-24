/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** handle_messag
*/

#include <stdio.h>
#include "../include/server.h"
#include "../include/prototype.h"

void handle_connected_client(char *buffer, client_fds_t *client_fds,
    data_t *data_server)
{
    if (user_commande(buffer, client_fds, data_server) == 0)
        return;
    if (team_commande(buffer, client_fds, data_server) == 0)
        return;
    if (channel_commande(buffer, client_fds, data_server) == 0)
        return;
    if (thread_commande(buffer, client_fds, data_server) == 0)
        return;
    if (pm_commande(buffer, client_fds, data_server) == 0)
        return;
    other_commande(buffer, client_fds);
}

void handle_message(char *buffer, client_fds_t *client_fds,
    data_t *data_server)
{
    if (client_fds->is_connected == NOT_CONNECTED ||
    client_fds->is_connected == CONNECTION_IN_PROGRESS) {
        handle_not_connected_client(buffer, client_fds, data_server);
    } else if (client_fds->is_connected == CONNECTED) {
        handle_connected_client(buffer, client_fds, data_server);
    }
}
