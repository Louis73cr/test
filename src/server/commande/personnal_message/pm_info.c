/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** pm_info
*/

#include "../../include/server.h"
#include "../../include/prototype.h"

int find_position_in_pm(client_fds_t *client_fds, data_t *data_server)
{
    if (client_fds->uuid_in_mp == NULL) {
        dprintf(client_fds->server_fd,
        "404 You are not in a private channel\n");
        return -1;
    }
    for (int i = 0; data_server->personal[i].uuid_mp != NULL;
    i++) {
        if (strcmp(client_fds->uuid_in_mp, data_server->personal[i].uuid_mp)
        == 0)
            return i;
    }
    return -1;
}

void info_pm(client_fds_t *client_fds, data_t *data_server)
{
    int position = 0;

    position = find_position_in_pm(client_fds, data_server);
    if (position == -1)
        return;
    if (strcmp(data_server->personal[position].user_uuid_1,
    client_fds->uuid_in_mp) != 0) {
        dprintf(client_fds->server_fd, "200 [%s] [%s]\n",
        data_server->personal[position].uuid_mp,
        data_server->personal[position].user_uuid_2);
        return;
    } else {
        dprintf(client_fds->server_fd, "200 [%s] [%s]\n",
        data_server->personal[position].uuid_mp,
        data_server->personal[position].user_uuid_1);
        return;
    }
}
