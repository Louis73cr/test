/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** team_save
*/

#include "../include/server.h"
#include "../include/prototype.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void no_team_file(data_t *data_server)
{
    printf("No team data found, creating default team\n");
    data_server->teams = malloc(sizeof(team_t) * 2);
    if (data_server->teams == NULL) {
        printf("Memory allocation failed");
        exit(EXIT_ERROR_EPITECH);
    }
    data_server->teams[0].team_name = NULL;
    data_server->teams[0].team_description = NULL;
    data_server->teams[0].team_uuid = NULL;
    data_server->teams[0].user_uuid = malloc(sizeof(char *));
    data_server->teams[0].user_uuid[0] = NULL;
    return;
}

void load_data2(int nb_users, char *token, data_t *data_server, int i)
{
    data_server->teams[i].user_uuid = malloc((nb_users + 1) * sizeof(char *));
    token = strtok(token, "()");
    for (int j = 0; j < nb_users; j++) {
        data_server->teams[i].user_uuid[j] = strdup(token);
        token = strtok(NULL, "()");
    }
    data_server->teams[i].user_uuid[nb_users] = NULL;
    data_server->teams[i].channels = malloc(sizeof(channel_t) * 2);
    data_server->teams[i].channels[0].channel_name = NULL;
    data_server->teams[i].channels[0].channel_description = NULL;
    data_server->teams[i].channels[0].channel_uuid = NULL;
    data_server->teams[i].channels[0].user_uuid = malloc(sizeof(char *));
    data_server->teams[i].channels[0].user_uuid[0] = NULL;
}

void count_users(char *token, int *nb_users)
{
    for (int j = 0; token[j] != '\0'; j++) {
        if (token[j] == '(')
            *nb_users += 1;
    }
}

void load_data(FILE *file, data_t *data_server, int nb_teams)
{
    char line[1024];
    int nb_users = 0;
    char *token = NULL;

    for (int i = 0; i < nb_teams; i++) {
        nb_users = 0;
        fgets(line, sizeof(line), file);
        data_server->teams[i].team_name = strdup(strtok(line, "[]"));
        data_server->teams[i].team_description = strdup(strtok(NULL, "[]"));
        data_server->teams[i].team_uuid = strdup(strtok(NULL, "[]"));
        token = strtok(NULL, "[]");
        count_users(token, &nb_users);
        load_data2(nb_users, token, data_server, i);
    }
}

void load_team(data_t *data_srv)
{
    FILE *file = fopen("data/team.conf", "rb");
    int nb_teams = 0;

    if (file == NULL)
        return no_team_file(data_srv);
    nb_teams = det_nb_line(file);
    fseek(file, 0, SEEK_SET);
    data_srv->teams = malloc((nb_teams + 1) * sizeof(team_t));
    load_data(file, data_srv, nb_teams);
    fclose(file);
    data_srv->teams[nb_teams].team_name = NULL;
    data_srv->teams[nb_teams].team_description = NULL;
    data_srv->teams[nb_teams].team_uuid = NULL;
    data_srv->teams[nb_teams].channels = malloc(sizeof(channel_t));
    data_srv->teams[nb_teams].channels[0].channel_name = NULL;
    data_srv->teams[nb_teams].channels[0].channel_description = NULL;
    data_srv->teams[nb_teams].channels[0].channel_uuid = NULL;
    data_srv->teams[nb_teams].channels[0].user_uuid = malloc(sizeof(char *));
    data_srv->teams[nb_teams].channels[0].user_uuid[0] = NULL;
}
