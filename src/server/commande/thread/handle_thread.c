/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** handle_thread
*/

#include "../../include/server.h"
#include "../../include/prototype.h"
#include "thread.h"

int find_pos_in_message2(client_fds_t *client_fds, data_t *data_server,
    int pos_in_team, int pos_in_channel)
{
    for (int i = 0; data_server->teams[pos_in_team].channels[pos_in_channel]
    .messages[i].thread.thread_uuid != NULL; i++) {
        if (strcmp(data_server->teams[pos_in_team].channels[pos_in_channel]
        .messages[i].thread.thread_uuid, client_fds->uuid_in_thread) == 0) {
            return i;
        }
    }
    return -1;
}

int find_pos_in_message(client_fds_t *client_fds, data_t *data_server,
    int pos_in_team, int pos_in_channel)
{
    for (int i = 0; data_server->teams[pos_in_team].channels[pos_in_channel]
    .messages[i].thread.title != NULL; i++) {
        if (strcmp(data_server->teams[pos_in_team].channels[pos_in_channel]
        .messages[i].thread.thread_uuid, client_fds->uuid_in_thread) == 0) {
            return i;
        }
    }
    return -1;
}

int find_pos_in_comment(data_t *data_server, thread_value_t pos)
{
    int i = 0;

    if (data_server->teams[pos.pos_in_team].channels[pos.pos_in_channel].
        messages[pos.pos_in_msg].thread.title == NULL) {
        return -1;
    }
    while (data_server->teams[pos.pos_in_team].channels[pos.pos_in_channel].
        messages[pos.pos_in_msg].thread.comment[i].comment != NULL)
        i++;
    return i;
}

int thread_commande2(char *buffer, client_fds_t *client_fds,
    data_t *data_server)
{
    if (strncmp(buffer, "THREAD_GM", 8) == 0) {
        thread_get_msg(client_fds, data_server);
        return 0;
    }
    if (strncmp(buffer, "THREAD_SM ", 10) == 0) {
        thread_send_msg(buffer + 10, client_fds, data_server);
        return 0;
    }
    return 1;
}

int thread_commande(char *buffer, client_fds_t *client_fds,
    data_t *data_server)
{
    if (strncmp(buffer, "THREAD_C ", 9) == 0) {
        thread_create(buffer + 9, client_fds, data_server);
        return 0;
    }
    if (strncmp(buffer, "THREAD_I", 8) == 0) {
        thread_info(client_fds, data_server);
        return 0;
    }
    if (strncmp(buffer, "THREAD_MV ", 10) == 0) {
        thread_move(buffer + 10, client_fds, data_server);
        return 0;
    }
    return thread_commande2(buffer, client_fds, data_server);
}
