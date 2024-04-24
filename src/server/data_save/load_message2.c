/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** load_message2
*/

#include "../include/prototype.h"
#include "../include/server.h"
#include "data_save.h"

void no_message2(data_t *data_server, int team_index, int channel_index)
{
    data_server->teams[team_index].channels[channel_index]
    .messages[0].thread.comment[0].comment = NULL;
    data_server->teams[team_index].channels[channel_index]
    .messages[0].thread.comment[0].user_uuid = NULL;
    data_server->teams[team_index].channels[channel_index]
    .messages[0].thread.comment[0].time_send = 0;
}

void no_message(data_t *data_server, int team_index, int channel_index)
{
    data_server->teams[team_index].channels[channel_index]
    .messages = malloc(sizeof(message_t) * 2);
    data_server->teams[team_index].channels[channel_index]
    .messages[0].message = NULL;
    data_server->teams[team_index].channels[channel_index]
    .messages[0].user_uuid = NULL;
    data_server->teams[team_index].channels[channel_index]
    .messages[0].time_send = 0;
    data_server->teams[team_index].channels[channel_index]
    .messages[0].thread.thread_uuid = NULL;
    data_server->teams[team_index].channels[channel_index]
    .messages[0].thread.title = NULL;
    data_server->teams[team_index].channels[channel_index]
    .messages[0].thread.description = NULL;
    data_server->teams[team_index].channels[channel_index]
    .messages[0].thread.comment = malloc(sizeof(comment_t) * 2);
    no_message2(data_server, team_index, channel_index);
}
