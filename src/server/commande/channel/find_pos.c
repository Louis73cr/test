/*
** EPITECH PROJECT, 2024
** B-NWP-400-PAR-4-1-myteams-louis.croci
** File description:
** find_pos
*/

#include "../../include/server.h"
#include "../../include/prototype.h"

int find_pos_in_team(client_fds_t *client_fds, data_t *data_server)
{
    for (int i = 0; data_server->teams[i].team_uuid != NULL; i++) {
        if (strcmp(client_fds->uuid_in_team,
            data_server->teams[i].team_uuid) == 0) {
            return i;
        }
    }
    return -1;
}

int find_pos_in_channel(client_fds_t *client_fds, data_t *data_server,
    int pos_in_team)
{
    for (int i = 0; data_server->teams[pos_in_team].channels[i].channel_uuid
        != NULL; i++) {
        if (strcmp(client_fds->uuid_in_channel,
            data_server->teams[pos_in_team].channels[i].channel_uuid) == 0) {
            return i;
        }
    }
    return -1;
}

int count_messages(data_t *data_server, int pos_in_team, int pos_in_channel)
{
    int nb_message = 0;

    for (int i = 0; data_server->teams[pos_in_team].
        channels[pos_in_channel].messages[i].user_uuid != NULL; i++) {
        nb_message++;
    }
    return nb_message;
}
