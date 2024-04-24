/*
** EPITECH PROJECT, 2024
** B-NWP-400-PAR-4-1-myteams-louis.croci
** File description:
** get_msg_channe_bis
*/

#include "../../include/server.h"
#include "../../include/prototype.h"

void print_data(data_t *data_server, int pos[], char *msg_buffer,
    int total_length_i[])
{
    sprintf(msg_buffer + total_length_i[0], "[(%s), (%s), (%s), (%s)], ",
        data_server->teams[pos[0]].channels[pos[1]].
            messages[total_length_i[1]].user_uuid,
        data_server->teams[pos[0]].channels[pos[1]].
            messages[total_length_i[1]].message,
        time_t_to_str(data_server->teams[pos[0]].
        channels[pos[1]].messages[total_length_i[1]].time_send),
        data_server->teams[pos[0]].channels[pos[1]].
            messages[total_length_i[1]].thread.thread_uuid);
}

int print_data2(data_t *data_server, int pos[], int i)
{
    return snprintf(NULL, 0, "[(%s), (%s), (%s), (%s)], ",
        data_server->teams[pos[0]].channels[pos[1]].messages[i].user_uuid,
        data_server->teams[pos[0]].channels[pos[1]].messages[i].message,
        time_t_to_str(data_server->teams[pos[0]].channels[pos[1]].
        messages[i].time_send), data_server->teams[pos[0]].channels[pos[1]].
            messages[i].thread.thread_uuid);
}

void last_print_get_msg(client_fds_t *client_fds, char *msg_buffer,
    int total_length)
{
    dprintf(client_fds->server_fd, total_length > 0 ?
        "200 %s\n" : "513 no message found in this channel\n", msg_buffer);
    free(msg_buffer);
}
