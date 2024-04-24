/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** move_team
*/

#include "../../include/server.h"
#include "../../include/prototype.h"

void move_team_suite(client_fds_t *client_fds,
    data_t *data_server, int i)
{
    for (int j = 0; data_server->teams[i].user_uuid[j] != NULL; j++) {
        if (strcmp(data_server->teams[i].user_uuid[j],
        client_fds->client_uuid) == 0) {
            client_fds->uuid_in_team = data_server->teams[i].team_uuid;
            client_fds->uuid_in_channel = NULL;
            client_fds->uuid_in_thread = NULL;
            dprintf(client_fds->server_fd, "200 Succes\n");
            return;
        }
    }
    dprintf(client_fds->server_fd, "513 Team not found\n");
}

void move_team(char *buffer, client_fds_t *client_fds, data_t *data_server)
{
    int nb_teams = 0;

    for (int i = 0; data_server->teams[i].team_uuid != NULL; i++)
        nb_teams++;
    for (int i = 0; i < nb_teams; i++) {
        if (strcmp(data_server->teams[i].team_uuid, buffer + 8) == 0) {
            move_team_suite(client_fds, data_server, i);
            return;
        }
    }
    dprintf(client_fds->server_fd, "401 Error with team name\n");
}

void move_team_reinit(client_fds_t *client_fds)
{
    client_fds->uuid_in_team = NULL;
    client_fds->uuid_in_channel = NULL;
    client_fds->uuid_in_thread = NULL;
    dprintf(client_fds->server_fd, "200 Succes\n");
}
