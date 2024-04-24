/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** set_new_loc
*/

#include "../../../../include/client.h"

int set_new_teams(char **buffer, client_t *client)
{
    char awnser[BUF_SIZE];
    char **awn_buff = NULL;

    dprintf(client->con.socket, "TEAM_MV %s\t\n", buffer[1]);
    if (server_awnser(&*awnser, client) == -1) {
        return -1;
    }
    awn_buff = my_str_to_word_array(awnser);
    if (strcmp(awn_buff[0], "200") == 0) {
        client->loc.team_uuid = buffer[1];
    } else {
        client_error_unknown_team(buffer[1]);
        free_array(awn_buff);
        return -1;
    }
    free_array(awn_buff);
    return 0;
}

int set_new_channel(char **buffer, client_t *client)
{
    char awnser[BUF_SIZE];
    char **buff = NULL;

    dprintf(client->con.socket, "CHANNEL_MV %s\t\n", buffer[2]);
    if (server_awnser(&*awnser, client) == -1) {
        return -1;
    }
    buff = my_str_to_word_array(awnser);
    if (strcmp(buff[0], "200") == 0) {
        client->loc.channel_uuid = buffer[2];
    } else {
        client_error_unknown_channel(buffer[1]);
        free_array(buff);
        return -1;
    }
    free_array(buff);
    return 0;
}

int set_new_thread(char **buffer, client_t *client)
{
    char awnser[BUF_SIZE];
    char **buff = NULL;

    dprintf(client->con.socket, "THREAD_MV %s\t\n", buffer[1]);
    if (server_awnser(&*awnser, client) == -1) {
        return -1;
    }
    buff = my_str_to_word_array(awnser);
    if (strcmp(buff[0], "200") == 0) {
        client->loc.thread_uuid = buffer[3];
    } else {
        client_error_unknown_thread(buffer[1]);
        free_array(buff);
        return -1;
    }
    free_array(buff);
    return 0;
}

int set_team_channel(char **buffer, client_t *client)
{
    if (set_new_teams(buffer, client) == -1) {
        return -1;
    }
    if (set_new_channel(buffer, client) == -1) {
        return -1;
    }
    return 0;
}

int set_all(char **buffer, client_t *client)
{
    if (set_team_channel(buffer, client) == -1) {
        return -1;
    }
    if (set_new_thread(buffer, client) == -1) {
        return -1;
    }
    return 0;
}
