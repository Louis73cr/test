/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** handle_users
*/

#include "../../../../include/client.h"

static int display_user_info(char **buff, int i)
{
    int status = 0;

    if (strcmp(buff[i + 2], "CONNECTED") == 0) {
        status = 1;
    }
    client_print_users(buff[i], buff[i + 1], status);
    return 0;
}

int parse_users(char **buffer)
{
    int b_size = get_buffer_size(buffer);

    if (b_size < 2) {
        return -1;
    }
    for (int i = 1; i < b_size; i++) {
        display_user_info(buffer, i);
        i += 3;
    }
    return 0;
}

int handle_users(char **buffer, client_t *client)
{
    char awn[BUF_SIZE];
    char **buff = NULL;

    if (get_buffer_size(buffer) != 1) {
        return -1;
    }
    dprintf(client->con.socket, "USER_G\t\n");
    if (server_awnser(&*awn, client) == -1) {
        return -1;
    }
    buff = my_str_to_word_array(awn);
    if (strcmp(buff[0], "200") == 0) {
        parse_users(buff);
    }
    free_array(buff);
    return 0;
}
