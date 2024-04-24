/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** hanndle_connections
*/

#include <stdio.h>
#include "../../include/server.h"
#include "../../include/prototype.h"

int check_value_username(const char *buffer, user_t *data_s)
{
    for (int i = 0; data_s[i].username != NULL; i++) {
        if (strncmp(buffer, data_s[i].username,
        strnlen(data_s[i].username, 4096)) == 0)
            return i;
    }
    return -1;
}

bool check_value_password(const char *buffer, user_t *data_s,
    const char *user_uuid)
{
    int witch_user = -1;

    for (int i = 0; data_s[i].username != NULL; i++) {
        if (strcmp(user_uuid, data_s[i].user_uuid) == 0) {
            witch_user = i;
            break;
        }
    }
    if (witch_user != -1 && strncmp(buffer, data_s[witch_user].password,
    strnlen(data_s[witch_user].password, 4096)) == 0)
        return true;
    return false;
}

void set_status_client(client_fds_t *client_fds, data_t *data_server)
{
    for (int i = 0; data_server->users[i].user_uuid != NULL; i++) {
        if (strcmp(data_server->users[i].user_uuid, client_fds->client_uuid)
        == 0) {
            data_server->users[i].status = CONNECTED;
            return;
        }
    }
}
