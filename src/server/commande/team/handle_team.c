/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** handle_team
*/

#include "../../include/server.h"
#include "../../include/prototype.h"

char *find_team_name(char *str)
{
    char *team_name = malloc(sizeof(char) * strlen(str));

    for (int i = 0; str[i] != '0'; i++) {
        team_name[i] = str[i];
        team_name[i + 1] = '\0';
    }
    return team_name;
}

int team_commande_end(char *buffer, client_fds_t *client_fds,
    data_t *data_server)
{
    if (strncmp(buffer, "TEAM_UI", 7) == 0) {
        get_user_in_team(data_server, client_fds);
        return 0;
    }
    return 1;
}

int team_commande_suite(char *buffer, client_fds_t *client_fds,
    data_t *data_server)
{
    if (strncmp(buffer, "TEAM_G", 6) == 0) {
        get_team(client_fds, data_server);
        return 0;
    }
    if (strncmp(buffer, "TEAM_I ", 7) == 0) {
        info_team(buffer, client_fds, data_server);
        return 0;
    }
    if (strncmp(buffer, "TEAM_MV ", 8) == 0) {
        move_team(buffer, client_fds, data_server);
        return 0;
    }
    if (strncmp(buffer, "TEAM_R", 6) == 0) {
        move_team_reinit(client_fds);
        return 0;
    }
    return team_commande_end(buffer, client_fds, data_server);
}

int team_commande(char *buffer, client_fds_t *client_fds, data_t *data_server)
{
    if (strncmp(buffer, "TEAM_C ", 7) == 0) {
        create_team(buffer, client_fds, data_server);
        return 0;
    }
    if (strncmp(buffer, "TEAM_J ", 7) == 0) {
        join_team(buffer, client_fds, data_server);
        return 0;
    }
    if (strncmp(buffer, "TEAM_L ", 7) == 0) {
        leave_team(buffer, client_fds, data_server);
        return 0;
    }
    if (strncmp(buffer, "TEAM_D ", 7) == 0) {
        delete_team(buffer, client_fds, data_server);
        return 0;
    }
    return team_commande_suite(buffer, client_fds, data_server);
}
