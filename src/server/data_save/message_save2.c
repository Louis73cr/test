/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** message_save2
*/

#include "../include/prototype.h"
#include "../include/server.h"
#include "data_save.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void no_message_file(data_t *data_server)
{
    if (data_server->teams == NULL) {
        printf("Memory allocation failed");
        exit(EXIT_ERROR_EPITECH);
    }
    data_server->teams[0].channels[0].messages = malloc(sizeof(message_t) * 2);
    data_server->teams[0].channels[0].messages[0].message = NULL;
    data_server->teams[0].channels[0].messages[0].user_uuid = NULL;
    data_server->teams[0].channels[0].messages[0].time_send = 0;
    data_server->teams[0].channels[0].messages[0].thread.thread_uuid = NULL;
    data_server->teams[0].channels[0].messages[0].thread.title = NULL;
    data_server->teams[0].channels[0].messages[0].thread.description = NULL;
    data_server->teams[0].channels[0].messages[0].thread.comment =
    malloc(sizeof(comment_t) * 2);
    data_server->teams[0].channels[0].messages[0].thread.comment[0].comment =
    NULL;
    data_server->teams[0].channels[0].messages[0].thread.comment[0].user_uuid
    = NULL;
    data_server->teams[0].channels[0].messages[0].thread.comment[0].time_send
    = 0;
    return;
}

int find_team_index_by_team_uuid(data_t *data_server, char *team_uuid)
{
    for (int i = 0; data_server->teams[i].team_uuid != NULL; i++) {
        if (strcmp(data_server->teams[i].team_uuid, team_uuid) == 0) {
            return i;
        }
    }
    return -1;
}

int find_channel_index(data_t *data_server,
    char *channel_uuid, int team_index)
{
    for (int i = 0; data_server->teams[team_index].channels[i]
    .channel_uuid != NULL; i++) {
        if (strcmp(data_server->teams[team_index].channels[i]
        .channel_uuid, channel_uuid) == 0) {
            return i;
        }
    }
    return -1;
}

void read_msg_end(data_t *data_server, message_s_t index, char *token)
{
    token = strtok(NULL, "()");
    if (strcmp(token, "null") == 0)
        data_server->teams[index.team].channels[index.channel]
        .messages[index.msg].thread.title = NULL;
    else
        data_server->teams[index.team].channels[index.channel]
        .messages[index.msg].thread.title = strdup(token);
    data_server->teams[index.team].channels[index.channel]
    .messages[index.msg].thread.description = NULL;
    data_server->teams[index.team].channels[index.channel]
    .messages[index.msg].thread.comment = malloc(sizeof(comment_t) * 2);
    data_server->teams[index.team].channels[index.channel]
    .messages[index.msg].thread.comment[0].comment = NULL;
    data_server->teams[index.team].channels[index.channel]
    .messages[index.msg].thread.comment[0].time_send = 0;
    data_server->teams[index.team].channels[index.channel]
    .messages[index.msg].thread.comment[0].user_uuid = NULL;
}

void read_msg(data_t *data_server, message_s_t index, char *token)
{
    token = strtok(token, "()");
    data_server->teams[index.team].channels[index.channel]
    .messages[index.msg].user_uuid = strdup(token);
    token = strtok(NULL, "()");
    data_server->teams[index.team].channels[index.channel]
    .messages[index.msg].message = strdup(token);
    token = strtok(NULL, "()");
    data_server->teams[index.team].channels[index.channel]
    .messages[index.msg].time_send = str_to_time_t(token);
    token = strtok(NULL, "()");
    if (strcmp(token, "null") == 0)
        data_server->teams[index.team].channels[index.channel]
        .messages[index.msg].thread.thread_uuid = NULL;
    else
        data_server->teams[index.team].channels[index.channel]
        .messages[index.msg].thread.thread_uuid = strdup(token);
    read_msg_end(data_server, index, token);
}
