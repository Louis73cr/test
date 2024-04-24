/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** thread_move
*/

#include "../../include/server.h"
#include "../../include/prototype.h"
#include "thread.h"

int check_pos2(data_t *data_server, client_fds_t *client_fds,
    int *pos_in_team, int *pos_in_channel)
{
    *pos_in_team = find_pos_in_team(client_fds, data_server);
    if (*pos_in_team == -1) {
        dprintf(client_fds->server_fd, "500 You are in any team\t\n");
        return -1;
    }
    *pos_in_channel = find_pos_in_channel(client_fds, data_server,
    *pos_in_team);
    if (*pos_in_channel == -1) {
        dprintf(client_fds->server_fd, "500 You are in any channel\t\n");
        return -1;
    }
    return 0;
}

void thread_move(char *buffer, client_fds_t *client_fds, data_t *data_server)
{
    int pos_in_team = 0;
    int pos_in_channel = 0;

    if (check_pos2(data_server, client_fds, &pos_in_team, &pos_in_channel)
    == -1)
        return;
    for (int i = 0; data_server->teams[pos_in_team].channels[pos_in_channel]
    .messages[i].thread.thread_uuid != NULL; i++) {
        if (strcmp(data_server->teams[pos_in_team].channels[pos_in_channel]
        .messages[i].thread.thread_uuid, buffer) == 0) {
            client_fds->uuid_in_thread = strdup(data_server->teams[pos_in_team]
            .channels[pos_in_channel].messages[i].thread.thread_uuid);
            dprintf(client_fds->server_fd, "200 Thread moved\t\n");
            return;
        }
    }
    dprintf(client_fds->server_fd, "200 Thread not find\t\n");
}
