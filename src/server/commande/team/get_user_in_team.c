/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** get_user_in_team
*/

#include "../../include/server.h"
#include "../../include/prototype.h"

void create_response(data_t *data_server, int i, char *user_ids)
{
    for (int j = 0; data_server->teams[i].user_uuid[j] != NULL; j++) {
        strcat(user_ids, "[");
        strcat(user_ids, data_server->teams[i].user_uuid[j]);
        strcat(user_ids, "], ");
    }
}

void get_user_in_team(data_t *data_server, client_fds_t *client_fds)
{
    char user_ids[1024] = "";

    if (client_fds->uuid_in_team == NULL) {
        dprintf(client_fds->server_fd, "404 You are not in any team\n");
        return;
    }
    for (int i = 0; data_server->teams[i].team_uuid != NULL; i++) {
        if (strcmp(data_server->teams[i].team_uuid, client_fds->uuid_in_team)
        == 0) {
            create_response(data_server, i, user_ids);
            break;
        }
    }
    if (strlen(user_ids) > 0) {
        user_ids[strlen(user_ids) - 2] = '\0';
        dprintf(client_fds->server_fd, "200 %s\n", user_ids);
    } else {
        dprintf(client_fds->server_fd, "404 No users found in your team\n");
    }
}
