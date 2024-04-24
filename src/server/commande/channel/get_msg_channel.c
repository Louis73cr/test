/*
** EPITECH PROJECT, 2024
** B-NWP-400-PAR-4-1-myteams-louis.croci
** File description:
** get_msg_channel
*/

#include "../../include/server.h"
#include "../../include/prototype.h"

void check_error_msg_buffer(char *msg_buffer)
{
    if (!msg_buffer) {
        printf("realloc");
        exit(EXIT_ERROR_EPITECH);
    }
}

int check_error_msg_buffer_malloc(char *msg_buffer)
{
    if (!msg_buffer) {
        printf("malloc");
        return 84;
    }
    return 0;
}

void fill_total_length_i(int total_length_i[], int total_length, int i)
{
    total_length_i[0] = total_length;
    total_length_i[1] = i;
}

void send_channel_messages(client_fds_t *client_fds,
    data_t *data_server, int pos[], int total_length_i[])
{
    char *msg_buffer = malloc(sizeof(char) * 10000);
    int total_length = 0;
    int msg_length = 0;

    if (check_error_msg_buffer_malloc(msg_buffer) == 84)
        return;
    for (int i = 0; data_server->teams[pos[0]].
        channels[pos[1]].messages[i].user_uuid != NULL; i++) {
        msg_length = print_data2(data_server, pos, i);
        if (total_length + msg_length >= 10000) {
            msg_buffer = realloc(msg_buffer, total_length + msg_length + 1);
            check_error_msg_buffer(msg_buffer);
        }
        fill_total_length_i(total_length_i, total_length, i);
        print_data(data_server, pos, msg_buffer, total_length_i);
        total_length += msg_length;
    }
    if (total_length > 0)
        msg_buffer[total_length - 2] = '\0';
    last_print_get_msg(client_fds, msg_buffer, total_length);
}

void get_msg_channel(client_fds_t *client_fds, data_t *data_server)
{
    int pos_team_channel[2] = {0, 0};
    int total_length_i[2] = {0, 0};

    if (!client_fds->uuid_in_team || !client_fds->uuid_in_channel) {
        dprintf(client_fds->server_fd,
            "404 You are not in a team or a channel\n");
        return;
    }
    pos_team_channel[0] = find_pos_in_team(client_fds, data_server);
    pos_team_channel[1] = find_pos_in_channel(client_fds, data_server,
        pos_team_channel[0]);
    send_channel_messages(client_fds, data_server,
        pos_team_channel, total_length_i);
}
