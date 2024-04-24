/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** join_team
*/

#include "../../include/server.h"
#include "../../include/prototype.h"

void set_join_team(int *nb_teams, int *pos_in_team, char *buffer,
    data_t *data_server)
{
    for (int i = 0; data_server->teams[i].team_uuid != NULL; i++)
        *nb_teams += 1;
    for (int i = 0; i < *nb_teams; i++) {
        if (strcmp(data_server->teams[i].team_uuid, buffer + 7) == 0) {
            *pos_in_team = i;
            return;
        }
    }
    *pos_in_team = -1;
}

void set_join_team_2(int *nb_users_in_team, int pos_in_team,
    data_t *data_server)
{
    for (int i = 0; data_server->teams[pos_in_team].user_uuid[i] != NULL; i++)
        *nb_users_in_team += 1;
}

void end_join_team(data_t *data_server, int pos_in_team, int nb_users_in_team,
    client_fds_t *client_fds)
{
    data_server->teams[pos_in_team].user_uuid = realloc(data_server->
    teams[pos_in_team].user_uuid, sizeof(char *) * (nb_users_in_team + 2));
    data_server->teams[pos_in_team].user_uuid[nb_users_in_team] =
    client_fds->client_uuid;
    data_server->teams[pos_in_team].user_uuid[nb_users_in_team + 1] = NULL;
    dprintf(client_fds->server_fd, "200 succes\n");
}

void join_team(char *buffer, client_fds_t *client_fds, data_t *data_server)
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
            dprintf(client_fds->server_fd, "513 You are in this team\n");
            return;
        }
    }
    end_join_team(data_server, pos_in_team, nb_users_in_team, client_fds);
    server_event_user_subscribed(buffer + 7, client_fds->client_uuid);
}
