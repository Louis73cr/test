/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** handle_unsubscribe
*/

#include "../../../../include/client.h"

int handle_unsubscribe(char **buffer, client_t *client)
{
    char awnser[BUF_SIZE];
    char **buff = NULL;

    if (get_buffer_size(buffer) != 2) {
        return -1;
    }
    dprintf(client->con.socket, "TEAM_L %s\t\n", buffer[1]);
    if (server_awnser(&*awnser, client) == -1) {
        return -1;
    }
    buff = my_str_to_word_array(awnser);
    if (strcmp(buff[0], "200") == 0) {
        client_print_unsubscribed(client->user.uuid, buffer[1]);
    } else {
        free_array(buff);
        return -1;
    }
    free_array(buff);
    return 0;
}
