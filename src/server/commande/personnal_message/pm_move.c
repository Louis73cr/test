/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** pm_move
*/

#include "../../include/server.h"
#include "../../include/prototype.h"

bool check_pm(client_fds_t *client_fds, data_t *data_server, int i)
{
    if (strcmp(client_fds->client_uuid,
    data_server->personal[i].user_uuid_1) == 0) {
        return true;
    }
    if (strcmp(client_fds->client_uuid,
    data_server->personal[i].user_uuid_2) == 0) {
        return true;
    }
    return false;
}

void move_pm(char *buffer, client_fds_t *client_fds, data_t *data_server)
{
    int position = -1;

    for (int j = 0; data_server->personal[j].uuid_mp != NULL; j++) {
        if (strcmp(data_server->personal[j].uuid_mp, buffer) == 0) {
            position = j;
            break;
        }
    }
    if (position == -1) {
        dprintf(client_fds->server_fd, "404 PM not found\n");
        return;
    }
    if (check_pm(client_fds, data_server, position) == false) {
        dprintf(client_fds->server_fd, "403 this is not your PM\n");
        return;
    }
    client_fds->uuid_in_mp = strdup(data_server->personal[position].uuid_mp);
    dprintf(client_fds->server_fd, "200 succes\n");
}
