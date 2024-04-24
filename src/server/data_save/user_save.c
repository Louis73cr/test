/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** user_save
*/

#include "../include/server.h"
#include "../include/prototype.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void save_user(data_t *data_server)
{
    FILE *file = fopen("data/user.conf", "wb");

    if (file == NULL) {
        printf("Error opening file");
        return;
    }
    for (int i = 0; data_server->users[i].user_uuid != NULL; i++) {
        fprintf(file, "[%s][%s][%s]\n", data_server->users[i].username,
        data_server->users[i].password, data_server->users[i].user_uuid);
    }
    fclose(file);
}

void no_conf_file(data_t *data_server)
{
    data_server->users = malloc(sizeof(user_t) * 2);
    if (data_server->users == NULL) {
        printf("Memory allocation failed");
        exit(EXIT_ERROR_EPITECH);
    }
    data_server->users[0].username = NULL;
    data_server->users[0].password = NULL;
    data_server->users[0].user_uuid = NULL;
    data_server->users[1].username = NULL;
    data_server->users[1].password = NULL;
    data_server->users[1].user_uuid = NULL;
    return;
}

void read_file(FILE *file, data_t *data_server, int nb_users)
{
    char line[1024];
    char *token;

    for (int i = 0; i < nb_users; i++) {
        fgets(line, sizeof(line), file);
        token = NULL;
        token = strtok(line, "[]");
        data_server->users[i].username = strdup(token);
        token = strtok(NULL, "[]");
        data_server->users[i].password = strdup(token);
        token = strtok(NULL, "[]");
        data_server->users[i].user_uuid = strdup(token);
        server_event_user_loaded(data_server->users[i].user_uuid,
        data_server->users[i].username);
    }
}

void load_user(data_t *data_server)
{
    FILE *file = fopen("data/user.conf", "rb");
    int nb_users = 0;

    if (file == NULL)
        return no_conf_file(data_server);
    nb_users = det_nb_line(file);
    fseek(file, 0, SEEK_SET);
    data_server->users = malloc((nb_users + 1) * sizeof(user_t));
    read_file(file, data_server, nb_users);
    fclose(file);
    data_server->users[nb_users].username = NULL;
    data_server->users[nb_users].password = NULL;
    data_server->users[nb_users].user_uuid = NULL;
}
