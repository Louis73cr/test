/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** thread_send_messag
*/

#include "../../include/server.h"
#include "../../include/prototype.h"
#include "thread.h"

void thread_data_msg2(data_t *data_server, thread_value_t pos, char *buffer,
    client_fds_t *client_fds)
{
    data_server->teams[pos.pos_in_team].channels[pos.pos_in_channel].messages
    [pos.pos_in_msg].thread.comment[pos.pos_in_comment].user_uuid =
    strdup(client_fds->client_uuid);
    data_server->teams[pos.pos_in_team].channels[pos.pos_in_channel].messages
    [pos.pos_in_msg].thread.comment[pos.pos_in_comment + 1].comment = NULL;
    data_server->teams[pos.pos_in_team].channels[pos.pos_in_channel].messages
    [pos.pos_in_msg].thread.comment[pos.pos_in_comment + 1].time_send = 0;
    data_server->teams[pos.pos_in_team].channels[pos.pos_in_channel].messages
    [pos.pos_in_msg].thread.comment[pos.pos_in_comment + 1].user_uuid = NULL;
    server_event_reply_created(client_fds->uuid_in_thread,
    client_fds->client_uuid, buffer);
}

void thread_data_msg(data_t *data_server, thread_value_t pos, char *buffer,
    client_fds_t *client_fds)
{
    data_server->teams[pos.pos_in_team].channels[pos.pos_in_channel].messages
    [pos.pos_in_msg].thread.comment = realloc(data_server->teams
    [pos.pos_in_team].channels[pos.pos_in_channel].messages
    [pos.pos_in_msg].thread.comment, sizeof(comment_t) * (pos.pos_in_comment
    + 2));
    data_server->teams[pos.pos_in_team].channels[pos.pos_in_channel].messages
    [pos.pos_in_msg].thread.comment[pos.pos_in_comment].comment =
    strdup(buffer);
    data_server->teams[pos.pos_in_team].channels[pos.pos_in_channel].messages
    [pos.pos_in_msg].thread.comment[pos.pos_in_comment].time_send =
    current_time();
    thread_data_msg2(data_server, pos, buffer, client_fds);
}

void thread_send_msg(char *buffer, client_fds_t *client_fds,
    data_t *data_server)
{
    thread_value_t pos;

    if (check_acces(client_fds, data_server, &pos) == -1)
        return;
    pos.pos_in_comment = find_pos_in_comment(data_server, pos);
    if (pos.pos_in_comment == -1) {
        dprintf(client_fds->server_fd,
        "500 Please create a thread for this message\t\n");
        return;
    }
    thread_data_msg(data_server, pos, buffer, client_fds);
    dprintf(client_fds->server_fd, "200 Message send\t\n");
}
