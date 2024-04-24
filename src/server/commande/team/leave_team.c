/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** leave_team
*/

#include "../../include/server.h"
#include "../../include/prototype.h"

void leave_team2(int i, int nb_users_in_team, data_t *data_server,
    int pos_in_team)
{
    for (int j = i; j < nb_users_in_team - 1; j++)
        data_server->teams[pos_in_team].user_uuid[j] =
        data_server->teams[pos_in_team].user_uuid[j + 1];
    data_server->teams[pos_in_team].user_uuid[nb_users_in_team - 1] = NULL;
}

void send_msg_lib_and_client(data_t *data_server, int pos_in_team,
    client_fds_t *client_fds)
{
    server_event_user_unsubscribed(data_server->teams[pos_in_team].team_uuid,
    client_fds->client_uuid);
    dprintf(client_fds->server_fd, "401 You're not in team\n");
}

void leave_team(char *buffer, client_fds_t *client_fds, data_t *data_server)
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
            leave_team2(i, nb_users_in_team, data_server, pos_in_team);
            dprintf(client_fds->server_fd, "200 Success\n");
            return;
        }
    }
    send_msg_lib_and_client(data_server, pos_in_team, client_fds);
}
