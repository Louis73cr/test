/*
** EPITECH PROJECT, 2024
** B-NWP-400-PAR-4-1-myteams-louis.croci
** File description:
** move_channel
*/

#include "../../include/server.h"
#include "../../include/prototype.h"

int find_team_position(client_fds_t *client_fds, data_t *data_server)
{
    int pos_in_team = 0;

    for (int i = 0; data_server->teams[i].team_uuid != NULL; i++) {
        if (strcmp(client_fds->uuid_in_team, data_server->teams[i].team_uuid)
            == 0)
            break;
        pos_in_team++;
    }
    return pos_in_team;
}

int find_user_in_channel(client_fds_t *client_fds, data_t *data_server,
    int pos_in_team, int pos[])
{
    if (strcmp(data_server->teams[pos_in_team].
        channels[pos[0]].user_uuid[pos[1]], client_fds->client_uuid) == 0) {
        client_fds->uuid_in_channel = data_server->teams[pos_in_team]
            .channels[pos[0]].channel_uuid;
        client_fds->uuid_in_thread = NULL;
        dprintf(client_fds->server_fd, "200 Succes\n");
        return 1;
    }
    return 0;
}

void check_channel(client_fds_t *client_fds, data_t *data_server, int team_i[])
{
    int pos[2] = {0, 0};

    for (int j = 0; data_server->teams[team_i[0]].
        channels[team_i[1]].user_uuid[j]
        != NULL; j++) {
        pos[0] = team_i[1];
        pos[1] = j;
        if (find_user_in_channel(client_fds, data_server, team_i[0], pos)) {
            return;
        }
    }
    dprintf(client_fds->server_fd, "513 Channel not found\n");
}

void check_and_move(client_fds_t *client_fds, data_t *data_server,
    char *buffer, int pos[])
{
    int team_i[2] = {0, 0};

    team_i[0] = pos[0];
    for (int i = 0; i < pos[1]; i++) {
        team_i[1] = i;
        if (strcmp(data_server->teams[pos[0]].channels[i].channel_uuid,
            buffer + 11) == 0) {
            check_channel(client_fds, data_server, team_i);
            return;
        }
    }
    dprintf(client_fds->server_fd, "401 Error with team name\n");
}

void move_channel(char *buffer, client_fds_t *client_fds, data_t *data_server)
{
    int team_channel[2] = {0, 0};

    team_channel[0] = find_team_position(client_fds, data_server);
    team_channel[1] = count_channels_in_team(data_server, team_channel[0]);
    check_and_move(client_fds, data_server, buffer, team_channel);
}
