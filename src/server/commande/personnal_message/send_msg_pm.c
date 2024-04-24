/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** send_pm
*/

#include "../../include/server.h"
#include "../../include/prototype.h"

int send_msg_pm2(int position, int *nb_msg, data_t *data_server)
{
    if (position == -1)
        return -1;
    while (data_server->personal[position].messages[*nb_msg].user_uuid !=
    NULL)
        *nb_msg += 1;
    if (*nb_msg == 0)
        data_server->personal[position].messages =
        malloc(sizeof(message_t) * 2);
    else
        data_server->personal[position].messages =
        realloc(data_server->personal[position].messages,
        sizeof(message_t) * (*nb_msg + 2));
    return 0;
}

void send_msg_pm(char *buffer, client_fds_t *client_fds, data_t *data_server)
{
    int position = 0;
    int nb_msg = 0;

    position = find_position_in_pm(client_fds, data_server);
    if (send_msg_pm2(position, &nb_msg, data_server) == -1)
        return;
    data_server->personal[position].messages[nb_msg].message = strdup(buffer);
    data_server->personal[position].messages[nb_msg].time_send = time(NULL);
    data_server->personal[position].messages[nb_msg].user_uuid =
    strdup(client_fds->client_uuid);
    data_server->personal[position].messages[nb_msg + 1].message = NULL;
    data_server->personal[position].messages[nb_msg + 1].time_send = 0;
    data_server->personal[position].messages[nb_msg + 1].user_uuid = NULL;
    dprintf(client_fds->server_fd, "200 succes\n");
    if (client_fds->client_uuid == data_server->personal[position].user_uuid_1)
        server_event_private_message_sended(client_fds->client_uuid,
        data_server->personal[position].user_uuid_1, buffer);
    else
        server_event_private_message_sended(client_fds->client_uuid,
        data_server->personal[position].user_uuid_2, buffer);
}
