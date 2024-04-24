/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** list_channel
*/

#include "../../../../include/client.h"

int display_channel(char **buff, char const *channel_uuid)
{
    client_team_print_channels(channel_uuid, buff[1], buff[2]);
    return 0;
}

int get_channel_info(char const *channel_uuid, client_t *client)
{
    char awnser[BUF_SIZE];
    char **buff = NULL;

    dprintf(client->con.socket, "CHANNEL_I %s\t\n", channel_uuid);
    if (server_awnser(&*awnser, client) == -1) {
        return -1;
    }
    buff = my_str_to_word_array(awnser);
    display_channel(buff, channel_uuid);
    free_array(buff);
    return 0;
}

int parse_channels(char **buff, client_t *client)
{
    int b_size = get_buffer_size(buff);

    if (b_size < 2) {
        return -1;
    }
    for (int i = 1; i < b_size - 1; i++) {
        if (strcmp(buff[i], ",") != 0) {
            get_channel_info(buff[i], client);
        }
    }
    return 0;
}

int show_all_channels(char **buffer, client_t *client)
{
    char awnser[BUF_SIZE];
    char **buff = NULL;

    if (get_buffer_size(buffer) != 1) {
        return -1;
    }
    dprintf(client->con.socket, "CHANNEL_G\t\n");
    if (server_awnser(&*awnser, client) == -1) {
        return -1;
    }
    buff = my_str_to_word_array(awnser);
    if (parse_channels(buff, client) == -1) {
        free_array(buff);
        return -1;
    }
    free_array(buff);
    return 0;
}
