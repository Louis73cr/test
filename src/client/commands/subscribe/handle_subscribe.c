/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** handle_subscribe
*/

#include "../../../../include/client.h"

int handle_subscribe(char **buffer, client_t *client)
{
    char awn[BUF_SIZE];
    char **buff = NULL;

    if (get_buffer_size(buffer) != 2)
        return -1;
    dprintf(client->con.socket, "TEAM_J %s\t\n", buffer[1]);
    if (server_awnser(&*awn, client) == -1)
        return -1;
    buff = my_str_to_word_array(awn);
    if (strcmp(buff[0], "200") == 0)
        client_print_subscribed(client->user.uuid, buffer[1]);
    else {
        dprintf(2, "Error while joining the team. Please try again.\n");
        free_array(buff);
        return -1;
    }
    free_array(buff);
    return 0;
}
