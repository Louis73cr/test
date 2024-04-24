/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** load_message
*/

#include "../include/prototype.h"
#include "../include/server.h"
#include "data_save.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void load_end_of_msg(data_t *data_server, int team_index, int channel_index,
    int nb_messages)
{
    data_server->teams[team_index].channels[channel_index]
    .messages[nb_messages].message = NULL;
    data_server->teams[team_index].channels[channel_index]
    .messages[nb_messages].user_uuid = NULL;
    data_server->teams[team_index].channels[channel_index]
    .messages[nb_messages].time_send = 0;
    data_server->teams[team_index].channels[channel_index]
    .messages[nb_messages].thread.thread_uuid = NULL;
    data_server->teams[team_index].channels[channel_index]
    .messages[nb_messages].thread.title = NULL;
    data_server->teams[team_index].channels[channel_index]
    .messages[nb_messages].thread.description = NULL;
    data_server->teams[team_index].channels[channel_index]
    .messages[nb_messages].thread.comment = NULL;
}

void load_msg(data_t *data_server, message_s_t index, char *token)
{
    int nb_messages = 0;
    char **messages = NULL;

    for (int j = 0; token[j] != '\0'; j++) {
        if (token[j] == '{')
            nb_messages++;
    }
    data_server->teams[index.team].channels[index.channel].messages
    = realloc(data_server->teams[index.team].channels[index.channel].
    messages, sizeof(message_t) * (nb_messages + 2));
    messages = malloc(sizeof(char *) * nb_messages);
    messages[0] = strtok(token, "{}");
    for (int j = 1; j < nb_messages; j++)
        messages[j] = strtok(NULL, "{}");
    for (index.msg = 0; index.msg < nb_messages; index.msg++)
        read_msg(data_server, index, messages[index.msg]);
    load_end_of_msg(data_server, index.team, index.channel, nb_messages);
}

void load_data_msg(FILE* file, data_t *data_server, int nb_teams)
{
    char *line = NULL;
    size_t len = 0;
    char *token = NULL;
    message_s_t index;

    for (int i = 0; i < nb_teams; i++) {
        line = NULL;
        len = 0;
        getline(&line, &len, file);
        token = strtok(line, "[]");
        index.team = find_team_index_by_team_uuid(data_server, token);
        token = strtok(NULL, "[]");
        index.channel = find_channel_index(data_server, token, index.team);
        token = strtok(NULL, "[]");
        if (token[0] == '\n')
            no_message(data_server, index.team, index.channel);
        else
            load_msg(data_server, index, token);
    }
}

void load_message(data_t *data_server)
{
    FILE *file = fopen("data/message.conf", "rb");
    int nb_message = 0;

    if (file == NULL)
        return no_message_file(data_server);
    nb_message = det_nb_line(file);
    fseek(file, 0, SEEK_SET);
    load_data_msg(file, data_server, nb_message);
    fclose(file);
}
