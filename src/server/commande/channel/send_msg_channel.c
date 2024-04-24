/*
** EPITECH PROJECT, 2024
** B-NWP-400-PAR-4-1-myteams-louis.croci
** File description:
** send_msg_channel
*/

#include "../../include/server.h"
#include "../../include/prototype.h"

int find_position_in_channel(client_fds_t *client_fds,
    data_t *data_server, int pos_in_team)
{
    for (int i = 0; data_server->teams[pos_in_team].
        channels[i].channel_uuid != NULL; i++) {
        if (strcmp(client_fds->uuid_in_channel,
            data_server->teams[pos_in_team].channels[i].channel_uuid) == 0) {
            return i;
        }
    }
    return -1;
}

void allocate_messages(data_t *data_server, int pos_in_team,
    int pos_in_channel, int nb_message)
{
    if (nb_message == 0)
        data_server->teams[pos_in_team].channels[pos_in_channel].messages =
            malloc(sizeof(message_t) * 2);
    else
        data_server->teams[pos_in_team].channels[pos_in_channel].messages =
            realloc(data_server->teams[pos_in_team].channels[pos_in_channel].
                messages, sizeof(message_t) * (nb_message + 2));
}

void end_of_creations(data_t *data_server, int pos_in_channel,
    int nb_message, int pos_in_team)
{
    data_server->teams[pos_in_team].channels[pos_in_channel].
        messages[nb_message].thread.comment = malloc(sizeof(comment_t *) * 2);
    data_server->teams[pos_in_team].channels[pos_in_channel].
        messages[nb_message].thread.comment[0].comment = NULL;
    data_server->teams[pos_in_team].channels[pos_in_channel].
        messages[nb_message].thread.comment[0].user_uuid = NULL;
    data_server->teams[pos_in_team].channels[pos_in_channel].
        messages[nb_message + 1].message = NULL;
    data_server->teams[pos_in_team].channels[pos_in_channel].
        messages[nb_message + 1].user_uuid = NULL;
    data_server->teams[pos_in_team].channels[pos_in_channel].
        messages[nb_message + 1].time_send = 0;
    data_server->teams[pos_in_team].channels[pos_in_channel].
        messages[nb_message + 1].thread.thread_uuid = NULL;
    data_server->teams[pos_in_team].channels[pos_in_channel].
        messages[nb_message + 1].thread.title = NULL;
    data_server->teams[pos_in_team].channels[pos_in_channel].
        messages[nb_message + 1].thread.description = NULL;
}

void create_message(data_t *data_server, int nb_message,
    client_fds_t *client_fds, char *msg)
{
    int pos_in_team = find_position_in_team(client_fds, data_server);
    int pos_in_channel = find_position_in_channel(client_fds,
        data_server, pos_in_team);

    data_server->teams[pos_in_team].channels[pos_in_channel].
        messages[nb_message].message = strdup(msg);
    data_server->teams[pos_in_team].channels[pos_in_channel].
        messages[nb_message].time_send = current_time();
    data_server->teams[pos_in_team].channels[pos_in_channel].
        messages[nb_message].user_uuid = strdup(client_fds->client_uuid);
    data_server->teams[pos_in_team].channels[pos_in_channel].
        messages[nb_message].thread.thread_uuid = uuid_generator();
    data_server->teams[pos_in_team].channels[pos_in_channel].
        messages[nb_message].thread.title = NULL;
    data_server->teams[pos_in_team].channels[pos_in_channel].
        messages[nb_message].thread.description = NULL;
    end_of_creations(data_server, pos_in_channel, nb_message, pos_in_team);
}

void send_msg_channel(client_fds_t *client_fds, data_t *data_server,
    char *msg)
{
    int pos_in_team = 0;
    int pos_in_channel = 0;
    int nb_message = 0;

    if (client_fds->uuid_in_team == 0 || client_fds->uuid_in_channel == 0) {
        dprintf(client_fds->server_fd,
            "404 You are not in a team or a channel\n");
        return;
    }
    pos_in_team = find_position_in_team(client_fds, data_server);
    pos_in_channel = find_position_in_channel(client_fds, data_server,
        pos_in_team);
    nb_message = count_messages(data_server, pos_in_team, pos_in_channel);
    allocate_messages(data_server, pos_in_team, pos_in_channel, nb_message);
    create_message(data_server, nb_message, client_fds, msg);
    dprintf(client_fds->server_fd, "200 Succes\n");
}
