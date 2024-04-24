/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** utils_team
*/

#include "../../include/server.h"
#include "../../include/prototype.h"

void create_team_suite(client_fds_t *client_fds, data_t *data_server,
    int nb_teams)
{
    data_server->teams[nb_teams].user_uuid[1] = NULL;
    data_server->teams[nb_teams].channels = malloc(sizeof(channel_t) * 2);
    data_server->teams[nb_teams].channels[0].channel_uuid = NULL;
    data_server->teams[nb_teams + 1].team_name = NULL;
    data_server->teams[nb_teams + 1].team_description = NULL;
    data_server->teams[nb_teams + 1].team_uuid = NULL;
    data_server->teams[nb_teams + 1].user_uuid = NULL;
    dprintf(client_fds->server_fd, "200 %s\n",
    data_server->teams[nb_teams].team_uuid);
    server_event_team_created(data_server->teams[nb_teams].team_uuid,
    data_server->teams[nb_teams].team_name, client_fds->client_uuid);
}

void create_team(char *buffer, client_fds_t *client_fds, data_t *data_server)
{
    int nb_teams = 0;
    int name_len = 0;

    while (data_server->teams[nb_teams].team_uuid != NULL)
        nb_teams++;
    while (buffer[name_len + 7] != '0')
        name_len++;
    if (data_server->teams == NULL)
        data_server->teams = malloc(sizeof(team_t) * 2);
    else
        data_server->teams = realloc(data_server->teams,
        sizeof(team_t) * (nb_teams + 2));
    data_server->teams[nb_teams].team_name = find_team_name(buffer + 7);
    data_server->teams[nb_teams].team_description =
    strdup(buffer + 7 + name_len + 1);
    data_server->teams[nb_teams].team_uuid = uuid_generator();
    data_server->teams[nb_teams].user_uuid = malloc(sizeof(char *) * 2);
    data_server->teams[nb_teams].user_uuid[0] = client_fds->client_uuid;
    create_team_suite(client_fds, data_server, nb_teams);
}
