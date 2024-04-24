/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** create_channel
*/

#include "../../../../include/client.h"

int cr_channel_server(char **buffer, client_t *client)
{
    char awnser[BUF_SIZE];
    char **buff = NULL;

    dprintf(client->con.socket, "CHANNEL_C %s0%s\t\n", buffer[1], buffer[2]);
    if (server_awnser(&*awnser, client) == -1) {
        return -1;
    }
    buff = my_str_to_word_array(awnser);
    if (strcmp(buff[0], "200") == 0) {
        client_event_channel_created(buff[1], buffer[1], buffer[2]);
        free_array(buff);
    } else {
        free_array(buff);
        return -1;
    }
    return 0;
}

int create_channel(char **buffer, client_t *client)
{
    if (get_buffer_size(buffer) != 3) {
        return -1;
    }
    if (cr_channel_server(buffer, client) == -1) {
        dprintf(2, "Error while creating channel. Please try again.\n");
    }
    return 0;
}
