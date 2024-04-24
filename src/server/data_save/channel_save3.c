/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** channel_save3
*/

#include "../include/server.h"
#include "../include/prototype.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void no_channel_file_2(data_t *data_server)
{
    data_server->teams[0].channels[0].messages[0].thread.thread_uuid = NULL;
    data_server->teams[0].channels[0].messages[0].thread.title = NULL;
    data_server->teams[0].channels[0].messages[0].thread.description = NULL;
    data_server->teams[0].channels[0].messages[0].thread.comment =
    malloc(sizeof(comment_t) * 2);
    data_server->teams[0].channels[0].messages[0].thread.comment[0].comment
    = NULL;
    data_server->teams[0].channels[0].messages[0].thread.comment[0].user_uuid
    = NULL;
    data_server->teams[0].channels[0].messages[0].thread.comment[0].time_send
    = 0;
}

void no_chanell_file(data_t *data_server)
{
    printf("No channel data found, creating default channel\n");
    data_server->teams[0].channels = malloc(sizeof(channel_t) * 2);
    data_server->teams[0].channels[0].channel_name = NULL;
    data_server->teams[0].channels[0].channel_description = NULL;
    data_server->teams[0].channels[0].channel_uuid = NULL;
    data_server->teams[0].channels[0].user_uuid = malloc(sizeof(char *));
    data_server->teams[0].channels[0].user_uuid[0] = NULL;
    data_server->teams[0].channels[0].messages = malloc(sizeof(message_t) * 2);
    data_server->teams[0].channels[0].messages[0].message = NULL;
    data_server->teams[0].channels[0].messages[0].user_uuid = NULL;
    data_server->teams[0].channels[0].messages[0].time_send = 0;
    no_channel_file_2(data_server);
}
