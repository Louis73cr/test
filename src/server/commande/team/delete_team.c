/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** delete_team
*/

#include "../../include/server.h"
#include "../../include/prototype.h"

void delete_team2(int nb_teams, data_t *data_server, int pos_in_team)
{
    for (int j = pos_in_team; j < nb_teams - 1; j++)
        data_server->teams[j] = data_server->teams[j + 1];
    data_server->teams[nb_teams - 1].team_uuid = NULL;
    data_server->teams[nb_teams - 1].channels->channel_uuid = NULL;
}

void check_pos(char *buffer, client_fds_t *client_fds)
{
    if (strcmp(buffer, client_fds->uuid_in_team) == 0)
        move_team_reinit(client_fds);
}

void delete_team(char *buffer, client_fds_t *client_fds, data_t *data_server)
{
    int nb_teams = 0;
    int nb_users_in_team = 0;
    int pos_in_team = 0;

    set_join_team(&nb_teams, &pos_in_team, buffer, data_server);
    if (pos_in_team == -1) {
        dprintf(client_fds->server_fd, "404 Team not found\n");
        return;
    }
    set_join_team_2(&nb_users_in_team, pos_in_team, data_server);
    for (int i = 0; i < nb_users_in_team; i++) {
        if (strcmp(data_server->teams[pos_in_team].user_uuid[i],
            client_fds->client_uuid) == 0) {
            delete_team2(nb_teams, data_server, pos_in_team);
            check_pos(buffer + 7, client_fds);
            dprintf(client_fds->server_fd, "200 Success\n");
            return;
        }
    }
    dprintf(client_fds->server_fd, "401 You're not in team\n");
}
