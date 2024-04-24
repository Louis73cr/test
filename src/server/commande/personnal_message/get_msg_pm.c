/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** get_msg_pm
*/

#include "../../include/server.h"
#include "../../include/prototype.h"

void get_msg_end(client_fds_t *client_fds, char *msg)
{
    if (strlen(msg) == 0) {
        dprintf(client_fds->server_fd, "404 No message in this PM\n");
        return;
    }
    msg[strlen(msg) - 2] = '\0';
    dprintf(client_fds->server_fd, "200 %s\n", msg);
}

void get_msg_pm(client_fds_t *client_fds, data_t *data_server)
{
    int position = 0;
    char msg[10000] = "";

    position = find_position_in_pm(client_fds, data_server);
    if (position == -1)
        return;
    for (int i = 0; data_server->personal[position].messages[i].user_uuid
    != NULL; i++) {
        strcat(msg, "[(");
        strcat(msg, data_server->personal[position].messages[i].user_uuid);
        strcat(msg, ") (");
        strcat(msg, data_server->personal[position].messages[i].message);
        strcat(msg, ") (");
        strcat(msg, time_t_to_str(data_server->personal[position].messages[i]
        .time_send));
        strcat(msg, ")], ");
    }
    get_msg_end(client_fds, msg);
}
