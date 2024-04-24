/*
** EPITECH PROJECT, 2024
** B-NWP-400-PAR-4-1-myteams-louis.croci
** File description:
** create_channel
*/

#include "../../include/server.h"
#include "../../include/prototype.h"

int count_channels(team_t *teams)
{
    int nb_channel = 0;

    for (int i = 0; teams->channels[i].channel_uuid != NULL; i++)
        nb_channel++;
    return nb_channel;
}

int count_channels_in_team(data_t *data_server, int pos_in_team)
{
    int nb_channel = 0;

    while (data_server->teams[pos_in_team].channels[nb_channel].channel_uuid
        != NULL)
        nb_channel++;
    return nb_channel;
}

void create_channel(char *buffer, client_fds_t *client_fds,
    data_t *data_server)
{
    int nb_channel = 0;
    int name_len = 0;
    int nbchannel_name_len[2] = {0, 0};
    team_t *teams = witch_team(client_fds, data_server);

    if (teams == NULL)
        return;
    for (int i = 0; teams->channels[i].channel_uuid != NULL; i++)
        nb_channel++;
    for (int i = 0; buffer[i] != '0'; i++)
        name_len++;
    name_len -= 10;
    nbchannel_name_len[0] = nb_channel;
    nbchannel_name_len[1] = name_len;
    update_channel(client_fds, teams, buffer, nbchannel_name_len);
    update_channel_triple(teams, nb_channel);
    server_event_channel_created(teams->team_uuid, teams->channels[nb_channel].
        channel_uuid, teams->channels[nb_channel].channel_name);
    dprintf(client_fds->server_fd, "200 %s\n",
        teams->channels[nb_channel].channel_uuid);
}
