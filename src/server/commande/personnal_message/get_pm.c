/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** get_pm
*/

#include "../../include/server.h"
#include "../../include/prototype.h"

void get_pm2(client_fds_t *client_fds, data_t *data_server, int i, char *msg)
{
    if (strcmp(data_server->personal[i].user_uuid_1,
    client_fds->client_uuid) == 0) {
        strcat(msg, "[");
        strcat(msg, data_server->personal[i].uuid_mp);
        strcat(msg, "], ");
    }
    if (strcmp(data_server->personal[i].user_uuid_2,
    client_fds->client_uuid) == 0) {
        strcat(msg, "[");
        strcat(msg, data_server->personal[i].uuid_mp);
        strcat(msg, "], ");
    }
}

void get_pm(client_fds_t *client_fds, data_t *data_server)
{
    char msg[10000] = "";

    for (int i = 0; data_server->personal[i].uuid_mp != NULL; i++) {
        get_pm2(client_fds, data_server, i, msg);
    }
    if (strlen(msg) == 0) {
        dprintf(client_fds->server_fd, "404 You don't have any PM\n");
        return;
    }
    msg[strlen(msg) - 2] = '\0';
    dprintf(client_fds->server_fd, "200 %s\n", msg);
}
