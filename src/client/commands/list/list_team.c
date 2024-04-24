/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** list_team
*/

#include "../../../../include/client.h"

int display_team(char **buff, char const *team_uuid)
{
    client_print_teams(team_uuid, buff[1], buff[2]);
    return 0;
}

int get_team_info(char const *team_uuid, client_t *client)
{
    char awnser[BUF_SIZE];
    char **buff = NULL;

    dprintf(client->con.socket, "TEAM_I %s\t\n", team_uuid);
    if (server_awnser(&*awnser, client) == -1) {
        return -1;
    }
    buff = my_str_to_word_array(awnser);
    for (int i = 0; buff[i] != NULL; i++) {
        printf("%s\n", buff[i]);
    }
    display_team(buff, team_uuid);
    return 0;
}

int parse_teams(char **buff, client_t *client)
{
    int b_size = get_buffer_size(buff);

    if (b_size < 2) {
        return -1;
    }
    for (int i = 1; i < b_size - 1; i++) {
        if (strcmp(buff[i], ",") != 0) {
            get_team_info(buff[i], client);
        }
    }
    return 0;
}

int show_all_teams(char **buffer, client_t *client)
{
    char awnser[BUF_SIZE];
    char **buff = NULL;

    if (get_buffer_size(buffer) != 1) {
        return -1;
    }
    dprintf(client->con.socket, "TEAM_G\t\n");
    if (server_awnser(&*awnser, client) == -1) {
        return -1;
    }
    buff = my_str_to_word_array(awnser);
    if (parse_teams(buff, client) == -1) {
        free_array(buff);
        return -1;
    }
    free_array(buff);
    return 0;
}
