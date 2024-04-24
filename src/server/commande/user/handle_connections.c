/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** hanndle_connections
*/

#include <stdio.h>
#include "../../include/server.h"
#include "../../include/prototype.h"

void new_user(const char *buffer, data_t *data_server, int num_user)
{
    data_server->users = realloc(data_server->users,
    sizeof(user_t) * (num_user + 2));
    data_server->users[num_user].username = strdup(buffer);
    data_server->users[num_user].user_uuid = uuid_generator();
    data_server->users[num_user].password = strdup("Pass");
    data_server->users[num_user].status = NOT_CONNECTED;
    data_server->users[num_user + 1].username = NULL;
    data_server->users[num_user + 1].user_uuid = NULL;
    data_server->users[num_user + 1].password = NULL;
    server_event_user_created(data_server->users[num_user].user_uuid,
    data_server->users[num_user].username);
}

int det_nb_user(data_t *data_server)
{
    int nb_user = 0;

    while (data_server->users[nb_user].username != NULL)
        nb_user++;
    return nb_user;
}

void give_username_commande(const char *buffer, client_fds_t *client_fds,
    data_t *data_server)
{
    int user_exist = check_value_username(&buffer[8], data_server->users);
    int nb_user = det_nb_user(data_server);

    if (user_exist != -1) {
        dprintf(client_fds->server_fd, "301 Need pasword\t\n");
        client_fds->is_connected = CONNECTION_IN_PROGRESS;
        client_fds->client_uuid = strdup(data_server->users[user_exist]
        .user_uuid);
        return;
    } else {
        new_user(&buffer[8], data_server, nb_user);
        client_fds->is_connected = CONNECTION_IN_PROGRESS;
        client_fds->client_uuid = strdup(data_server->users[nb_user]
        .user_uuid);
        dprintf(client_fds->server_fd, "301 Need pasword for new user\t\n");
        return;
    }
}

void give_password_commande(const char *buffer, client_fds_t *client_fds,
    data_t *data_server)
{
    if (client_fds->is_connected == NOT_CONNECTED) {
        dprintf(client_fds->server_fd, "500 Username is nedeed\t\n");
        return;
    }
    if (!check_value_password(&buffer[8], data_server->users,
    client_fds->client_uuid)) {
        dprintf(client_fds->server_fd, "501 Error with password\t\n");
        client_fds->is_connected = NOT_CONNECTED;
        free(client_fds->client_uuid);
        client_fds->client_uuid = NULL;
        return;
    } else {
        dprintf(client_fds->server_fd, "200 [%s]\t\n",
        client_fds->client_uuid);
        dprintf(client_fds->server_fd, "200 Success\t\n");
        set_status_client(client_fds, data_server);
        server_event_user_logged_in(client_fds->client_uuid);
        client_fds->is_connected = CONNECTED;
        return;
    }
}

void handle_not_connected_client(char *buffer, client_fds_t *client_fds,
    data_t *data_server)
{
    if (strncmp(buffer, "USER_CO ", 8) == 0) {
        give_username_commande(buffer, client_fds, data_server);
        return;
    } else if (strncmp(buffer, "USER_CP ", 8) == 0) {
        give_password_commande(buffer, client_fds, data_server);
    } else {
        dprintf(client_fds->server_fd, "500 Need to be connected\t\n");
    }
}
