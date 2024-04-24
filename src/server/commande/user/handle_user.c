/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** user_command
*/

#include "../../include/server.h"
#include "../../include/prototype.h"
#include <unistd.h>

void user_logout(client_fds_t *client_fds)
{
    if (client_fds->is_connected == NOT_CONNECTED ||
        client_fds->is_connected == CONNECTION_IN_PROGRESS) {
        dprintf(client_fds->server_fd, "500 Need to be connected\t\n");
    } else {
        dprintf(client_fds->server_fd, "200 Success\t\n");
        server_event_user_logged_out(client_fds->client_uuid);
        client_fds->is_connected = NOT_CONNECTED;
        client_fds->client_uuid = 0;
        client_fds->uuid_in_channel = NULL;
        client_fds->uuid_in_team = NULL;
        client_fds->uuid_in_thread = NULL;
        close(client_fds->server_fd);
    }
}

void user_info(client_fds_t *client_fds, data_t *data_server)
{
    char user_ids[1024] = "";

    for (int i = 0; data_server->users[i].user_uuid != NULL; i++) {
        strcat(user_ids, "[(");
        strcat(user_ids, data_server->users[i].user_uuid);
        strcat(user_ids, ") (");
        strcat(user_ids, data_server->users[i].username);
        if (data_server->users[i].status == CONNECTED)
            strcat(user_ids, ") (CONNECTED)], ");
        else
            strcat(user_ids, ") (NOT_CONNECTED)], ");
    }
    if (strlen(user_ids) > 0) {
        user_ids[strlen(user_ids) - 2] = '\0';
        dprintf(client_fds->server_fd, "200 %s\t\n", user_ids);
    } else {
        dprintf(client_fds->server_fd, "404 No users found\n");
    }
}

int user_commande(char *buffer, client_fds_t *client_fds, data_t *data_server)
{
    if (strncmp(buffer, "USER_L", 6) == 0) {
        user_logout(client_fds);
        return 0;
    }
    if (strncmp(buffer, "USER_G", 6) == 0) {
        user_info(client_fds, data_server);
        return 0;
    }
    return 1;
}
