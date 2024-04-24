/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** message_save
*/

#include "../include/prototype.h"
#include "../include/server.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void save_message_data(FILE *file, data_t *data_server, int i, int j)
{
    fprintf(file, "[");
    for (int k = 0; data_server->teams[i].channels[j].messages[k].message
    != NULL; k++) {
        fprintf(file, "{(%s)(%s)(%s)", data_server->teams[i].channels[j].
        messages[k].user_uuid, data_server->teams[i].channels[j].messages[k]
        .message, time_t_to_str(data_server->teams[i].channels[j].messages[k].
        time_send));
        if (data_server->teams[i].channels[j].messages[k].thread.thread_uuid
        == NULL)
            fprintf(file, "(null)");
        else
            fprintf(file, "(%s)", data_server->teams[i].channels[j].messages[k]
            .thread.thread_uuid);
        if (data_server->teams[i].channels[j].messages[k].thread.title == NULL)
            fprintf(file, "(null)}");
        else
            fprintf(file, "(%s)}", data_server->teams[i].channels[j].
            messages[k].thread.title);
    }
    fprintf(file, "]\n");
}

void save_message_switch(FILE *file, data_t *data_server, int i, int j)
{
    if (data_server->teams[i].channels[j].messages[0].message == NULL) {
        fprintf(file, "[]\n");
    } else {
        save_message_data(file, data_server, i, j);
    }
}

void save_message(data_t *data_server)
{
    FILE *file = fopen("data/message.conf", "wb");

    if (file == NULL) {
        printf("Error opening file");
        return;
    }
    for (int i = 0; data_server->teams[i].team_uuid != NULL; i++) {
        for (int j = 0; data_server->teams[i].channels[j].channel_uuid
        != NULL; j++) {
            fprintf(file, "[%s]", data_server->teams[i].team_uuid);
            fprintf(file, "[%s]", data_server->teams[i].channels[j].
            channel_uuid);
            save_message_switch(file, data_server, i, j);
        }
    }
    fclose(file);
}

void no_message_file_2(data_t *data_server, int i, int j)
{
    data_server->teams[i].channels[j].messages =
    malloc(sizeof(message_t) * 2);
    data_server->teams[i].channels[j].messages[0].message = NULL;
    data_server->teams[i].channels[j].messages[0].user_uuid = NULL;
    data_server->teams[i].channels[j].messages[0].time_send = 0;
    data_server->teams[i].channels[j].messages[0]
    .thread.thread_uuid = NULL;
    data_server->teams[i].channels[j].messages[0].thread.title = NULL;
    data_server->teams[i].channels[j].messages[0]
    .thread.description = NULL;
    data_server->teams[i].channels[j].messages[0]
    .thread.comment = malloc(sizeof(comment_t) * 2);
    data_server->teams[i].channels[j].messages[0]
    .thread.comment[0].comment = NULL;
    data_server->teams[i].channels[j].messages[0]
    .thread.comment[0].user_uuid = NULL;
    data_server->teams[i].channels[j].messages[0]
    .thread.comment[0].time_send = 0;
}
