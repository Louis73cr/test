/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** info_team
*/

#include "../../include/server.h"
#include "../../include/prototype.h"

void info_team(char *buffer, client_fds_t *client_fds, data_t *data_server)
{
    int nb_teams = 0;

    for (int i = 0; data_server->teams[i].team_uuid != NULL; i++)
        nb_teams++;
    for (int i = 0; i < nb_teams; i++) {
        if (strcmp(data_server->teams[i].team_uuid, buffer + 7) == 0) {
            dprintf(client_fds->server_fd, "200 [%s] [%s]\n",
            data_server->teams[i].team_name,
            data_server->teams[i].team_description);
            return;
        }
    }
    dprintf(client_fds->server_fd, "401 Error with team name\n");
}
