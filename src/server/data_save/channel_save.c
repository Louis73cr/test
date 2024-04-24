/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** channel_save
*/

#include "../include/server.h"
#include "../include/prototype.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int load_channel_file(data_t *d_s, char *token, int *p_i_c, int t_i)
{
    int nb_users = 0;

    for (int j = 0; d_s->teams[t_i].channels[j].channel_uuid != NULL; j++)
        (*p_i_c) += 1;
    d_s->teams[t_i].channels = realloc(d_s->teams[t_i].channels,
    (*p_i_c + 2) * sizeof(channel_t));
    token = pic_data(d_s, token, *p_i_c, t_i);
    for (int j = 0; token[j] != '\0'; j++) {
        if (token[j] == '(')
            nb_users++;
    }
    d_s->teams[t_i].channels[*p_i_c].user_uuid =
    malloc((nb_users + 1) * sizeof(char *));
    for (int j = 0; j < nb_users; j++) {
        token = strtok(token, "()");
        d_s->teams[t_i].channels[*p_i_c].user_uuid[j] = strdup(token);
    }
    return nb_users;
}

void load_end_node2(data_t *data_server, int team_index,
    int pos_in_channel)
{
    data_server->teams[team_index].channels[pos_in_channel].
    messages[0].thread.thread_uuid = NULL;
    data_server->teams[team_index].channels[pos_in_channel].
    messages[0].thread.title = NULL;
    data_server->teams[team_index].channels[pos_in_channel].
    messages[0].thread.description = NULL;
    data_server->teams[team_index].channels[pos_in_channel].
    messages[0].thread.comment = NULL;
    data_server->teams[team_index].channels[pos_in_channel + 1]
    .channel_uuid = NULL;
    data_server->teams[team_index].channels[pos_in_channel + 1]
    .channel_name = NULL;
    data_server->teams[team_index].channels[pos_in_channel + 1]
    .user_uuid = NULL;
    data_server->teams[team_index].channels[pos_in_channel + 1]
    .messages = NULL;
}

void load_end_node(data_t *data_server, int team_index,
    int pos_in_channel, int nb_users)
{
    data_server->teams[team_index].channels[pos_in_channel].
    user_uuid[nb_users] = NULL;
    data_server->teams[team_index].channels[pos_in_channel].
    messages = malloc(sizeof(message_t) * 2);
    data_server->teams[team_index].channels[pos_in_channel].
    messages[0].message = NULL;
    data_server->teams[team_index].channels[pos_in_channel].
    messages[0].user_uuid = NULL;
    data_server->teams[team_index].channels[pos_in_channel].
    messages[0].time_send = 0;
    load_end_node2(data_server, team_index, pos_in_channel);
}

void process_channel_data(FILE *file, data_t *data_server, int
    nb_channels)
{
    char line[1024];
    int pos_in_channel = 0;
    char *token = NULL;
    int team_index = 0;
    int nb_users = 0;

    for (int i = 0; i < nb_channels; i++) {
        pos_in_channel = 0;
        fgets(line, 1024, file);
        token = strtok(line, "[]");
        team_index = find_team_index_by_channel_uuid(data_server,
        token);
        nb_users = load_channel_file(data_server, token,
        &pos_in_channel, team_index);
        load_end_node(data_server, team_index, pos_in_channel,
        nb_users);
    }
}

void load_channel(data_t *data_server)
{
    FILE *file = fopen("data/channel.conf", "rb");
    int nb_channels = 0;

    if (file == NULL) {
        no_chanell_file(data_server);
        return;
    }
    nb_channels = det_nb_line(file);
    fseek(file, 0, SEEK_SET);
    process_channel_data(file, data_server, nb_channels);
    fclose(file);
}
