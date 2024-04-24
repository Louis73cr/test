/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** handle_logout
*/

#include "../../../../include/include.h"
#include "../../../../include/client.h"

static int handle_user_logout(client_t *client)
{
    char awnser[BUF_SIZE];
    char **buff = NULL;

    dprintf(client->con.socket, "USER_L\t\n");
    if (server_awnser(&*awnser, client) == -1)
        return -1;
    buff = my_str_to_word_array(awnser);
    if (strcmp(buff[0], "200") == 0) {
        client_event_logged_out(client->user.uuid, client->user.name);
        client->user.name = NULL;
        client->user.uuid = NULL;
        free_array(buff);
        return DISCONNECT;
    } else {
        free_array(buff);
        dprintf(2, "Error, while logging out. Please try again.\n");
        return 0;
    }
}

int handle_logout(char **buffer, client_t *client)
{
    if (get_buffer_size(buffer) != 1) {
        dprintf(2, "Too much arguments for the `logout` command.");
        return -1;
    }
    if (client->user.name != NULL) {
        if (handle_user_logout(client) == DISCONNECT)
            return DISCONNECT;
    } else {
        dprintf(2, "You are not logged in.\n");
        return -1;
    }
    return 0;
}
