/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** send_msg_channel2
*/

#include "../../include/server.h"
#include "../../include/prototype.h"

int find_position_in_team(client_fds_t *client_fds, data_t *data_server)
{
    for (int i = 0; data_server->teams[i].team_uuid != NULL; i++) {
        if (strcmp(client_fds->uuid_in_team, data_server->teams[i].team_uuid)
            == 0)
            return i;
    }
    return -1;
}
