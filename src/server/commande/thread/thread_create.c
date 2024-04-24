/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** thread_create
*/

#include "../../include/server.h"
#include "../../include/prototype.h"
#include "thread.h"

void give_data2(client_fds_t *client_fds, data_t *data_server,
    thread_value_t pos)
{
    server_event_thread_created(client_fds->uuid_in_channel,
    client_fds->uuid_in_thread, client_fds->client_uuid,
    data_server->teams[pos.pos_in_team].channels[pos.pos_in_channel]
    .messages[pos.pos_in_msg].thread.title, data_server->teams[pos.pos_in_team]
    .channels[pos.pos_in_channel].messages[pos.pos_in_msg].thread.description);
    dprintf(client_fds->server_fd, "200 Thread created\t\n");
}

void give_data(client_fds_t *client_fds, data_t *data_server,
    thread_value_t pos, char *buffer)
{
    data_server->teams[pos.pos_in_team].channels[pos.pos_in_channel]
    .messages[pos.pos_in_msg].thread.title = find_team_name(buffer);
    data_server->teams[pos.pos_in_team].channels[pos.pos_in_channel]
    .messages[pos.pos_in_msg].thread.description
    = strdup(buffer + pos.name_len + 1);
    data_server->teams[pos.pos_in_team].channels[pos.pos_in_channel]
    .messages[pos.pos_in_msg].thread.time_send = current_time();
    data_server->teams[pos.pos_in_team].channels[pos.pos_in_channel]
    .messages[pos.pos_in_msg].thread.comment = malloc(sizeof(comment_t));
    data_server->teams[pos.pos_in_team].channels[pos.pos_in_channel]
    .messages[pos.pos_in_msg].thread.comment[0].comment = NULL;
    data_server->teams[pos.pos_in_team].channels[pos.pos_in_channel]
    .messages[pos.pos_in_msg].thread.comment[0].time_send = 0;
    data_server->teams[pos.pos_in_team].channels[pos.pos_in_channel]
    .messages[pos.pos_in_msg].thread.comment[0].user_uuid = NULL;
    give_data2(client_fds, data_server, pos);
}

void thread_create(char *buffer, client_fds_t *client_fds, data_t *data_server)
{
    thread_value_t pos;

    if (client_fds->uuid_in_thread == NULL) {
        dprintf(client_fds->server_fd, "500 you are in any thread\t\n");
        return;
    }
    if (check_acces2(client_fds, data_server, &pos) == -1)
        return;
    while (buffer[pos.name_len] != '0')
        pos.name_len += 1;
    if (data_server->teams[pos.pos_in_team].channels[pos.pos_in_channel]
    .messages[pos.pos_in_msg].thread.title == NULL) {
        give_data(client_fds, data_server, pos, buffer);
    } else {
        dprintf(client_fds->server_fd, "500 Thread already exist\t\n");
    }
}
