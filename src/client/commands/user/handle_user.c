/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** handle_user
*/

#include "../../../../include/client.h"

static int display_user_info(char **buffer, int idx)
{
    int status = 0;

    if (strcmp(buffer[idx + 2], "CONNECTED") == 0) {
        status = 1;
    }
    client_print_users(buffer[idx], buffer[idx + 1], status);
    return 0;
}

int parse_user(char **buffer, char const *user_uuid)
{
    int b_size = get_buffer_size(buffer);

    if (b_size < 2) {
        return -1;
    }
    for (int i = 1; i < b_size; i++) {
        if (strcmp(user_uuid, buffer[i]) == 0) {
            display_user_info(buffer, i);
        }
    }
    return 0;
}

int handle_user(char **buffer, client_t *client)
{
    char awn[BUF_SIZE];
    char **buff = NULL;

    if (get_buffer_size(buffer) != 2) {
        return -1;
    }
    dprintf(client->con.socket, "USER_G %s\t\n", buffer[1]);
    if (server_awnser(&*awn, client) == -1) {
        return -1;
    }
    buff = my_str_to_word_array(awn);
    if (strcmp(buff[0], "200") == 0) {
        parse_user(buff, buffer[1]);
    } else {
        dprintf(2, "Error, user doesn't exist.\n");
    }
    free_array(buff);
    return 0;
}
