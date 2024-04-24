/*
** EPITECH PROJECT, 2024
** B-NWP-400-PAR-4-1-myteams-louis.croci
** File description:
** delete_channel
*/

#include "../../include/server.h"
#include "../../include/prototype.h"

void free_channel_resources(channel_t *channel)
{
    free(channel->channel_name);
    free(channel->channel_description);
    free(channel->user_uuid);
    free(channel->channel_uuid);
}

void shift_channels(team_t *teams, int start, int end)
{
    for (int j = start; j < end; j++)
        teams->channels[j] = teams->channels[j + 1];
}

void find_and_delete_channel(team_t *teams, char *buffer, int nb_channel,
    client_fds_t *client_fds)
{
    for (int i = 0; i < nb_channel; i++) {
        if (strcmp(teams->channels[i].channel_uuid, buffer + 10) == 0) {
            free_channel_resources(&teams->channels[i]);
            shift_channels(teams, i, nb_channel);
            dprintf(client_fds->server_fd, "200 Succes\n");
            return;
        }
    }
    dprintf(client_fds->server_fd, "404 Channel not found\n");
}

void delete_channel(char *buffer, client_fds_t *client_fds,
    data_t *data_server)
{
    int nb_channel = 0;
    team_t *teams = witch_team(client_fds, data_server);

    if (teams == NULL)
        return;
    nb_channel = count_channels(teams);
    find_and_delete_channel(teams, buffer, nb_channel, client_fds);
}
