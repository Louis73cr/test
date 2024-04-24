/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** thread_info
*/

#include "../../include/server.h"
#include "../../include/prototype.h"
#include "thread.h"

void init_pos(thread_value_t *pos)
{
    pos->pos_in_team = 0;
    pos->pos_in_channel = 0;
    pos->pos_in_msg = 0;
    pos->pos_in_comment = 0;
    pos->name_len = 0;
}

int check_acces2(client_fds_t *client_fds, data_t *data_server,
    thread_value_t *pos)
{
    init_pos(pos);
    pos->pos_in_team = find_pos_in_team(client_fds, data_server);
    if (pos->pos_in_team == -1) {
        dprintf(client_fds->server_fd, "500 You are in any team\t\n");
        return -1;
    }
    pos->pos_in_channel = find_pos_in_channel(client_fds, data_server,
    pos->pos_in_team);
    if (pos->pos_in_channel == -1) {
        dprintf(client_fds->server_fd, "500 You are in any channel\t\n");
        return -1;
    }
    pos->pos_in_msg = find_pos_in_message2(client_fds, data_server,
    pos->pos_in_team, pos->pos_in_channel);
    if (pos->pos_in_msg == -1) {
        dprintf(client_fds->server_fd, "500 You are in any message\t\n");
        return -1;
    }
    return 0;
}

int check_acces(client_fds_t *client_fds, data_t *data_server,
    thread_value_t *pos)
{
    init_pos(pos);
    pos->pos_in_team = find_pos_in_team(client_fds, data_server);
    if (pos->pos_in_team == -1) {
        dprintf(client_fds->server_fd, "500 You are in any team\t\n");
        return -1;
    }
    pos->pos_in_channel = find_pos_in_channel(client_fds, data_server,
    pos->pos_in_team);
    if (pos->pos_in_channel == -1) {
        dprintf(client_fds->server_fd, "500 You are in any channel\t\n");
        return -1;
    }
    pos->pos_in_msg = find_pos_in_message(client_fds, data_server,
    pos->pos_in_team, pos->pos_in_channel);
    if (pos->pos_in_msg == -1) {
        dprintf(client_fds->server_fd, "500 You are in any message\t\n");
        return -1;
    }
    return 0;
}

void thread_info(client_fds_t *client_fds, data_t *data_server)
{
    thread_value_t pos;

    if (client_fds->uuid_in_thread == NULL) {
        dprintf(client_fds->server_fd, "500 you are in any thread\t\n");
        return;
    }
    if (check_acces(client_fds, data_server, &pos) == -1)
        return;
    if (data_server->teams[pos.pos_in_team].channels[pos.pos_in_channel]
    .messages[pos.pos_in_msg].thread.title == NULL) {
        dprintf(client_fds->server_fd, "500 Please create a thread\t\n");
        return;
    }
    dprintf(client_fds->server_fd, "200 [(%s) (%s) (%s)]\n",
    data_server->teams[pos.pos_in_team].channels[pos.pos_in_channel]
    .messages[pos.pos_in_msg].thread.thread_uuid,
    data_server->teams[pos.pos_in_team].channels[pos.pos_in_channel]
    .messages[pos.pos_in_msg].thread.title,
    data_server->teams[pos.pos_in_team].channels[pos.pos_in_channel]
    .messages[pos.pos_in_msg].thread.description);
}
