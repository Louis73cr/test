/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** handle_channel
*/

#include "../../include/server.h"
#include "../../include/prototype.h"

char *find_channel_name(char *str)
{
    char *team_name = malloc(sizeof(char) * strlen(str));

    for (int i = 0; str[i] != '0'; i++) {
        team_name[i] = str[i];
        team_name[i + 1] = '\0';
    }
    return team_name;
}

team_t *witch_team(client_fds_t *client_fds, data_t *data_server)
{
    int witch_teams = 0;

    if (client_fds->uuid_in_team == NULL) {
        dprintf(client_fds->server_fd,
        "404 You move in any team. Use TEAM_MV to enter in a team\n");
        return NULL;
    }
    for (int i = 0; data_server->teams[i].team_uuid
    != client_fds->uuid_in_team; i++) {
        if (data_server->teams[i].team_uuid == NULL) {
            dprintf(client_fds->server_fd, "404 Team not found\n");
            return NULL;
        }
        witch_teams++;
    }
    return &data_server->teams[witch_teams];
}

void info_channel(char *buffer, client_fds_t *client_fds, data_t *data_server)
{
    int nb_channel = 0;
    team_t *teams = witch_team(client_fds, data_server);

    if (teams == NULL)
        return;
    for (int i = 0; teams->channels[i].channel_uuid != NULL; i++)
        nb_channel++;
    for (int i = 0; i < nb_channel; i++) {
        if (strcmp(teams->channels[i].channel_uuid, buffer + 10) == 0) {
            dprintf(client_fds->server_fd, "200 %s %s\n",
            teams->channels[i].channel_name,
            teams->channels[i].channel_description);
            return;
        }
    }
    dprintf(client_fds->server_fd, "404 Channel not found\n");
}

int channel_commande2(char *buffer,
    client_fds_t *client_fds, data_t *data_server)
{
    if (strncmp(buffer, "CHANNEL_I ", 10) == 0) {
        info_channel(buffer, client_fds, data_server);
        return 0;
    }
    if (strncmp(buffer, "CHANNEL_MV ", 11) == 0) {
        move_channel(buffer, client_fds, data_server);
        return 0;
    }
    if (strncmp(buffer, "CHANNEL_G", 9) == 0) {
        get_channel(client_fds, data_server);
        return 0;
    }
    return 1;
}

int channel_commande(char *buffer,
    client_fds_t *client_fds, data_t *data_server)
{
    if (strncmp(buffer, "CHANNEL_GM", 10) == 0) {
        get_msg_channel(client_fds, data_server);
        return 0;
    }
    if (strncmp(buffer, "CHANNEL_SM ", 11) == 0) {
        send_msg_channel(client_fds, data_server, buffer + 11);
        return 0;
    }
    if (strncmp(buffer, "CHANNEL_C ", 10) == 0) {
        create_channel(buffer, client_fds, data_server);
        return 0;
    }
    if (strncmp(buffer, "CHANNEL_D ", 10) == 0) {
        delete_channel(buffer, client_fds, data_server);
        return 0;
    }
    if (!channel_commande2(buffer, client_fds, data_server)) {
        return 0;
    }
    return 1;
}
