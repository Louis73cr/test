/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** handle_info
*/

#include "../../../../include/client.h"

int display_user_info(client_t *client)
{
    client_print_user(client->user.uuid, client->user.name, 1);
    return 0;
}

int display_team_info(client_t *client)
{
    char awn[BUF_SIZE];
    char **buff = NULL;

    dprintf(client->con.socket, "TEAM_I %s\t\n", client->loc.team_uuid);
    if (server_awnser(&*awn, client) == -1) {
        return -1;
    }
    buff = my_str_to_word_array(awn);
    if (strcmp(buff[0], "200") == 0) {
        client_print_team(client->loc.team_uuid, buff[1], buff[2]);
    }
    free_array(buff);
    return 0;
}

int display_channel_info(client_t *client)
{
    char awn[BUF_SIZE];
    char **buff = NULL;

    dprintf(client->con.socket, "CHANNEL_I %s\t\n", client->loc.channel_uuid);
    if (server_awnser(&*awn, client) == -1) {
        return -1;
    }
    buff = my_str_to_word_array(awn);
    if (strcmp(buff[0], "200") == 0) {
        client_print_channel(client->loc.channel_uuid, buff[1], buff[2]);
    }
    free_array(buff);
    return 0;
}

int display_thread_info(client_t *client)
{
    char awn[BUF_SIZE];
    char **buff = NULL;

    dprintf(client->con.socket, "THREAD_I %s\t\n", client->loc.thread_uuid);
    if (server_awnser(&*awn, client) == -1) {
        return -1;
    }
    buff = my_str_to_word_array(awn);
    if (strcmp(buff[0], "200") == 0) {
        client_print_thread(client->loc.thread_uuid, buff[1], (time_t)buff[2],
        buff[3], buff[4]);
    }
    free_array(buff);
    return 0;
}

int handle_info(char **buffer, client_t *client)
{
    int idx = user_position_index(client);

    if (get_buffer_size(buffer) != 1) {
        return -1;
    }
    if (idx == 0)
        display_user_info(client);
    if (idx == 1)
        display_team_info(client);
    if (idx == 2)
        display_channel_info(client);
    if (idx == 3)
        display_thread_info(client);
    return 0;
}
