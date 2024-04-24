/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** team_save2
*/

#include "../include/server.h"
#include "../include/prototype.h"

void save_team(data_t *data_server)
{
    FILE *file = fopen("data/team.conf", "wb");

    if (file == NULL) {
        printf("Error opening file");
        return;
    }
    for (int i = 0; data_server->teams[i].team_uuid != NULL; i++) {
        fprintf(file, "[%s][%s][%s]", data_server->teams[i].team_name,
        data_server->teams[i].team_description,
        data_server->teams[i].team_uuid);
        fprintf(file, "[");
        for (int j = 0; data_server->teams[i].user_uuid[j] != NULL; j++) {
            fprintf(file, "(%s)", data_server->teams[i].user_uuid[j]);
        }
        fprintf(file, "]\n");
    }
    fclose(file);
}
