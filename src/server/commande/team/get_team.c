/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** get_team
*/

#include "../../include/server.h"
#include "../../include/prototype.h"
#include "team.h"

void get_team_suite(client_fds_t *client_fds, data_t *data_server,
    get_t *get)
{
    if (strcmp(data_server->teams[get->i].user_uuid[get->j],
    client_fds->client_uuid) == 0) {
        if (get->get_team == NULL)
            sprintf(get->get_team, "[%s], ",
            data_server->teams[get->i].team_uuid);
        else {
            strcat(get->get_team, "[");
            strcat(get->get_team, data_server->teams[get->i].team_uuid);
            strcat(get->get_team, "], ");
        }
    }
}

void get_team(client_fds_t *client_fds, data_t *data_server)
{
    int nb_users_in_team = 0;
    get_t get;

    get.get_team = malloc(sizeof(char) * 10000);
    get.get_team[0] = '\0';
    for (get.i = 0; data_server->teams[get.i].team_uuid != NULL; get.i++) {
        nb_users_in_team = 0;
        while (data_server->teams[get.i].user_uuid[nb_users_in_team] != NULL)
            nb_users_in_team++;
        for (get.j = 0; get.j < nb_users_in_team; get.j++)
            get_team_suite(client_fds, data_server, &get);
    }
    if (get.get_team[0] != '\0') {
        get.get_team[strlen(get.get_team) - 2] = '\0';
        dprintf(client_fds->server_fd, "200 %s\n", get.get_team);
    } else
        dprintf(client_fds->server_fd, "513 You are in any team\n");
    free(get.get_team);
}
