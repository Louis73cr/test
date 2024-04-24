/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** handle_subscribed
*/

#include "../../../../include/client.h"

int display_sub_teams(client_t *client)
{
    char awn[BUF_SIZE];
    char **buff = NULL;

    dprintf(client->con.socket, "TEAM_G\t\n");
    if (server_awnser(&*awn, client) == -1) {
        return -1;
    }
    buff = my_str_to_word_array(awn);
    if (strcmp(buff[0], "200") == 0) {
        parse_teams(buff, client);
    }
    free_array(buff);
    return 0;
}

int display_user_in_team(char **buffer, client_t *client)
{
    char awn[BUF_SIZE];
    char **buff = NULL;

    dprintf(client->con.socket, "TEAM_UI %s\t\n", buffer[1]);
    if (server_awnser(&*awn, client) == -1) {
        return -1;
    }
    buff = my_str_to_word_array(awn);
    if (strcmp(buff[0], "200") == 0) {
        printf("%s\n", awn);
    }
    return 0;
}

int handle_subscribed(char **buffer, client_t *client)
{
    if (get_buffer_size(buffer) == 1) {
        display_sub_teams(client);
    } else if (get_buffer_size(buffer) == 2) {
        display_user_in_team(buffer, client);
    } else {
        return -1;
    }
    return 0;
}
