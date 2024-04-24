/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** channel_save2
*/

#include "../include/server.h"
#include "../include/prototype.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void save_channel(data_t *data_server)
{
    FILE *file = fopen("data/channel.conf", "wb");

    if (file == NULL) {
        printf("Error opening file");
        return;
    }
    for (int i = 0; data_server->teams[i].team_uuid != NULL; i++) {
        for (int j = 0; data_server->teams[i].channels[j].channel_uuid
        != NULL; j++) {
            write_channel_data(file, data_server->teams[i].channels[j],
            data_server->teams[i].team_uuid);
        }
    }
    fclose(file);
}

int find_team_index_by_channel_uuid(data_t *data_server, char *team_uuid)
{
    for (int i = 0; data_server->teams[i].team_uuid != NULL; i++) {
        if (strcmp(data_server->teams[i].team_uuid, team_uuid) == 0) {
            return i;
        }
    }
    return -1;
}

char *pic_data(data_t *data_server, char *token, int pos_in_channel,
    int team_index)
{
    token = strtok(NULL, "[]");
    data_server->teams[team_index].channels[pos_in_channel].
    channel_name = strdup(token);
    token = strtok(NULL, "[]");
    data_server->teams[team_index].channels[pos_in_channel].
    channel_description = strdup(token);
    token = strtok(NULL, "[]");
    data_server->teams[team_index].channels[pos_in_channel].
    channel_uuid = strdup(token);
    token = strtok(NULL, "[]");
    return token;
}

void write_channel_data(FILE *file, channel_t channel, char *team_uuid)
{
    fprintf(file, "[%s][%s][%s][%s]", team_uuid,
    channel.channel_name,
    channel.channel_description,
    channel.channel_uuid);
    fprintf(file, "[");
    for (int k = 0; channel.user_uuid[k] != NULL; k++)
        fprintf(file, "(%s)", channel.user_uuid[k]);
    fprintf(file, "]\n");
}
