/*
** EPITECH PROJECT, 2024
** B-NWP-400-PAR-4-1-myteams-louis.croci
** File description:
** get_channel
*/

#include "../../include/server.h"
#include "../../include/prototype.h"

int count_users_in_channel(channel_t *channel)
{
    int nb_users_in_channel = 0;

    while (channel->user_uuid[nb_users_in_channel] != NULL)
        nb_users_in_channel++;
    return nb_users_in_channel;
}

bool is_user_in_channel(channel_t *channel,
    char *client_uuid, int nb_users_in_channel)
{
    for (int j = 0; j < nb_users_in_channel; j++) {
        if (strcmp(channel->user_uuid[j], client_uuid) == 0) {
            return true;
        }
    }
    return false;
}

void append_channel_to_string(char *get_channel, char *channel_uuid)
{
    strcat(get_channel, "[");
    strcat(get_channel, channel_uuid);
    strcat(get_channel, "], ");
}

void get_channel(client_fds_t *client_fds, data_t *data_server)
{
    team_t *teams = witch_team(client_fds, data_server);
    int nb_users_in_channel = 0;
    char *get_channel = malloc(sizeof(char) * 10000);

    get_channel[0] = '\0';
    for (int i = 0; teams->channels[i].channel_uuid != NULL; i++) {
        nb_users_in_channel = count_users_in_channel(&teams->channels[i]);
        if (is_user_in_channel(&teams->channels[i], client_fds->client_uuid,
            nb_users_in_channel)) {
            append_channel_to_string(get_channel,
            teams->channels[i].channel_uuid);
        }
    }
    if (get_channel[0] != '\0') {
        get_channel[strlen(get_channel) - 2] = '\0';
        dprintf(client_fds->server_fd, "200 %s\n", get_channel);
    } else
        dprintf(client_fds->server_fd, "513 Channel not found\n");
    free(get_channel);
}
