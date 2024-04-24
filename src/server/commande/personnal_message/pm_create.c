/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** pm_create
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../../include/server.h"
#include "../../include/prototype.h"

void create_pm2(char *buffer, client_fds_t *client_fds, data_t *data_server)
{
    for (int i = 0; data_server->personal[i].uuid_mp != NULL; i++) {
        if ((strcmp(data_server->personal[i].user_uuid_1,
        client_fds->client_uuid) == 0 &&
            strcmp(data_server->personal[i].user_uuid_2, buffer + 5) == 0) || (
            strcmp(data_server->personal[i].user_uuid_2,
            client_fds->client_uuid) == 0 &&
            strcmp(data_server->personal[i].user_uuid_1, buffer + 5) == 0)) {
            dprintf(client_fds->server_fd,
            "403 You already have a PM with this user\n");
            return;
        }
    }
}

void create_pm_end(data_t *data_server, int nb_pm, char *buffer,
    client_fds_t *client_fds)
{
    data_server->personal[nb_pm].uuid_mp = uuid_generator();
    data_server->personal[nb_pm].user_uuid_1 = strdup(client_fds->client_uuid);
    data_server->personal[nb_pm].user_uuid_2 = strdup(buffer + 5);
    data_server->personal[nb_pm].messages = malloc(sizeof(message_t) * 2);
    data_server->personal[nb_pm].messages[0].message = NULL;
    data_server->personal[nb_pm].messages[0].time_send = 0;
    data_server->personal[nb_pm].messages[0].user_uuid = NULL;
    data_server->personal[nb_pm + 1].uuid_mp = NULL;
    data_server->personal[nb_pm + 1].user_uuid_1 = NULL;
    data_server->personal[nb_pm + 1].user_uuid_2 = NULL;
    data_server->personal[nb_pm + 1].messages = malloc(sizeof(message_t) * 2);
    data_server->personal[nb_pm + 1].messages[0].message = NULL;
    data_server->personal[nb_pm + 1].messages[0].time_send = 0;
    data_server->personal[nb_pm + 1].messages[0].user_uuid = NULL;
}

void create_pm(char *buffer, client_fds_t *client_fds, data_t *data_server)
{
    int nb_pm = 0;

    if (data_server->personal[nb_pm].uuid_mp != NULL)
        nb_pm++;
    if (nb_pm == 0)
        data_server->personal = malloc(sizeof(personal_t) * 2);
    else {
        data_server->personal = realloc(data_server->personal,
        sizeof(personal_t) * (nb_pm + 2));
        if (client_fds->client_uuid == buffer + 5) {
            dprintf(client_fds->server_fd,
            "403 You can't send a message to yourself\n");
            return;
        }
        create_pm2(buffer, client_fds, data_server);
    }
    create_pm_end(data_server, nb_pm, buffer, client_fds);
    dprintf(client_fds->server_fd, "200 %s\n",
    data_server->personal[nb_pm].uuid_mp);
}
