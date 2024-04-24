/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** thread_get_msg
*/

#include "../../include/server.h"
#include "../../include/prototype.h"
#include "thread.h"

void thread_get_data(data_t *data_server, thread_value_t pos,
    char *msg_buffer, int i)
{
    char *tmp = (char *)malloc(1000 * sizeof(char));

    snprintf(tmp, 1000, "[(%s) (%s) (%s)]", data_server->teams
    [pos.pos_in_team].channels[pos.pos_in_channel]
    .messages[pos.pos_in_msg].thread.comment[i].comment,
    data_server->teams[pos.pos_in_team].channels[pos.pos_in_channel]
    .messages[pos.pos_in_msg].thread.comment[i].user_uuid,
    time_t_to_str(data_server->teams[pos.pos_in_team].channels
    [pos.pos_in_channel].messages[pos.pos_in_msg].thread.comment[i]
    .time_send));
    strcat(msg_buffer, tmp);
    strcat(msg_buffer, ", ");
    free(tmp);
}

void sender(char *msg_buffer, client_fds_t *client_fds)
{
    if (strlen(msg_buffer) > 0)
        msg_buffer[strlen(msg_buffer) - 2] = '\0';
    else {
        dprintf(client_fds->server_fd,
        "513 no comment found in this thread\n");
        return;
    }
    dprintf(client_fds->server_fd, "200 %s\n", msg_buffer);
}

void thread_get_msg(client_fds_t *client_fds, data_t *data_server)
{
    char msg_buffer[10000] = "";
    thread_value_t pos;

    if (check_acces(client_fds, data_server, &pos) == -1)
        return;
    if (data_server->teams[pos.pos_in_team].channels[pos.pos_in_channel]
    .messages[pos.pos_in_msg].thread.title == NULL) {
        dprintf(client_fds->server_fd,
        "500 Please create a thread for this message\n");
        return;
    }
    for (int i = 0; data_server->teams[pos.pos_in_team].channels
    [pos.pos_in_channel].messages[pos.pos_in_msg].thread.comment[i]
    .comment != NULL; i++)
        thread_get_data(data_server, pos, msg_buffer, i);
    sender(msg_buffer, client_fds);
}
