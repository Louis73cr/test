/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** new_user
*/

#include "../../../../include/client.h"

int create_password(client_t *client)
{
    char awn[BUF_SIZE];
    char **buff = NULL;

    dprintf(client->con.socket, "USER_CP Pass\t\n");
    if (server_awnser(&*awn, client) == -1) {
        return -1;
    }
    buff = my_str_to_word_array(awn);
    if (strcmp(buff[0], "200") == 0) {
        last_check(client);
    }
    free_array(buff);
    return 0;
}

int create_new_user(char **buffer, client_t *client)
{
    char awn[BUF_SIZE];
    char **buff = NULL;

    dprintf(client->con.socket, "USER_C %s\t\n", buffer[1]);
    if (server_awnser(&*awn, client) == -1) {
        return -1;
    }
    buff = my_str_to_word_array(awn);
    if (strcmp(buff[0], "301") == 0) {
        create_password(client);
    } else {
        free_array(buff);
        return -1;
    }
    free_array(buff);
    return 0;
}
