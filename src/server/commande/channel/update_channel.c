/*
** EPITECH PROJECT, 2024
** B-NWP-400-PAR-4-1-myteams-louis.croci
** File description:
** update_channel
*/

#include "../../include/server.h"
#include "../../include/prototype.h"

void update_channel_bis(client_fds_t *client_fds, team_t *teams,
    char *buffer, int nbchannel_name_len[])
{
    teams->channels = realloc(teams->channels,
        sizeof(team_t) * (nbchannel_name_len[0] + 2));
    teams->channels[nbchannel_name_len[0]].channel_name =
        find_channel_name(buffer + 10);
    teams->channels[nbchannel_name_len[0]].channel_description =
        strdup(buffer + 10 + nbchannel_name_len[1] + 1);
    teams->channels[nbchannel_name_len[0]].user_uuid =
        realloc(teams->channels[nbchannel_name_len[0]].
            user_uuid, sizeof(char *) * (2));
    teams->channels[nbchannel_name_len[0]].user_uuid[0] =
        client_fds->client_uuid;
    teams->channels[nbchannel_name_len[0]].user_uuid[1] = NULL;
    teams->channels[nbchannel_name_len[0]].channel_uuid = uuid_generator();
    teams->channels[nbchannel_name_len[0]].messages =
        malloc(sizeof(message_t) * 2);
    teams->channels[nbchannel_name_len[0]].messages[0].message = NULL;
}

void update_channel(client_fds_t *client_fds,
    team_t *teams, char *buffer, int nbchannel_name_len[])
{
    update_channel_bis(client_fds, teams, buffer, nbchannel_name_len);
    teams->channels[nbchannel_name_len[0]].messages[0].user_uuid = NULL;
    teams->channels[nbchannel_name_len[0]].messages[0].time_send = 0;
    teams->channels[nbchannel_name_len[0]].messages[0].
        thread.thread_uuid = NULL;
    teams->channels[nbchannel_name_len[0]].messages[0].thread.title = NULL;
    teams->channels[nbchannel_name_len[0]].messages[0].thread.description
    = NULL;
    teams->channels[nbchannel_name_len[0]].messages[0].
        thread.comment = malloc(sizeof(comment_t) * 2);
    teams->channels[nbchannel_name_len[0]].messages[0].
        thread.comment[0].comment = NULL;
    teams->channels[nbchannel_name_len[0]].messages[0].
        thread.comment[0].time_send = 0;
    teams->channels[nbchannel_name_len[0]].messages[0].
        thread.comment[0].user_uuid = NULL;
}

void update_channel_triple(team_t *teams, int nb_channel)
{
    teams->channels[nb_channel + 1].channel_name = NULL;
    teams->channels[nb_channel + 1].channel_description = NULL;
    teams->channels[nb_channel + 1].channel_uuid = NULL;
    teams->channels[nb_channel + 1].user_uuid = NULL;
}
