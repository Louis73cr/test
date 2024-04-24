/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** load_thread
*/

#include "../include/prototype.h"
#include "../include/server.h"
#include "data_save.h"

void pos_in_team(data_t *data_server, char *token, message_s_t *pos)
{
    for (int i = 0; data_server->teams[i].team_uuid != NULL; i++) {
        if (strcmp(data_server->teams[i].team_uuid, token) == 0)
            break;
        pos->team += 1;
    }
}

void pos_in_channel(data_t *data_server, char *token, message_s_t *pos)
{
    for (int i = 0; data_server->teams[pos->team].channels[i].channel_uuid
    != NULL; i++) {
        if (strcmp(data_server->teams[pos->team].channels[i].channel_uuid,
        token) == 0)
            break;
        pos->channel += 1;
    }
}

void pos_in_thread(data_t *data_server, char *token, message_s_t *pos)
{
    for (int i = 0; data_server->teams[pos->team].channels[pos->channel]
    .messages[i].thread.thread_uuid != NULL; i++) {
        if (strcmp(data_server->teams[pos->team].channels[pos->channel]
        .messages[i].thread.thread_uuid, token) == 0)
            break;
        pos->msg += 1;
    }
}

int nb_comment_in_thread(char *token)
{
    int nb_comment = 0;

    for (int i = 0; token[i] != '\0'; i++) {
        if (token[i] == '{')
            nb_comment += 1;
    }
    return nb_comment;
}

void msg_data_loop(data_t *data_server, char *token_line, message_s_t pos,
    int pos_comment)
{
    char *copy_token_line = strdup(token_line);
    char *token_msg = strtok(copy_token_line, "()");

    data_server->teams[pos.team].channels[pos.channel].messages[pos.msg]
    .thread.comment[pos_comment].user_uuid = strdup(token_msg);
    token_msg = strtok(NULL, "()");
    data_server->teams[pos.team].channels[pos.channel].messages[pos.msg]
    .thread.comment[pos_comment].comment = strdup(token_msg);
    token_msg = strtok(NULL, "()");
    data_server->teams[pos.team].channels[pos.channel].messages[pos.msg]
    .thread.comment[pos_comment].time_send = str_to_time_t(token_msg);
    free(copy_token_line);
}
