/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** handle_login
*/

#include "../../../../include/include.h"
#include "../../../../include/client.h"

int last_check(client_t *client)
{
    char awnser[BUF_SIZE];
    char **buff;

    if (server_awnser(&*awnser, client) == -1) {
        return -1;
    }
    buff = my_str_to_word_array(awnser);
    if (strcmp(buff[0], "200") == 0) {
        free_array(buff);
    } else {
        free_array(buff);
        return -1;
    }
    return 0;
}

static int fill_user_info(client_t *client, char *user_uuid, char *name)
{
    client->user.name = name;
    client->user.uuid = user_uuid;
    client_event_logged_in(user_uuid, name);
    return 0;
}

static int handle_password_awnser(client_t *client, char *user_name)
{
    char awnser[BUF_SIZE];
    char **awn_buff = NULL;

    dprintf(client->con.socket, "USER_CP Pass\t\n");
    if (server_awnser(&*awnser, client) == -1)
        return -1;
    awn_buff = my_str_to_word_array(awnser);
    if (strcmp(awn_buff[0], "200") == 0) {
        if (last_check(client) == -1) {
            free_array(awn_buff);
            return -1;
        }
        fill_user_info(client, awn_buff[1], user_name);
    } else {
        free_array(awn_buff);
        return -1;
    }
    free_array(awn_buff);
    return 0;
}

int handle_login(char **buffer, client_t *client)
{
    char awnser[BUF_SIZE];
    char **awn_buff = NULL;

    if (client->user.name != NULL) {
        dprintf(2, "You are already logged in. Please log out before.\n");
        return 0;
    }
    if (get_buffer_size(buffer) != 2)
        return -1;
    dprintf(client->con.socket, "USER_CO %s\t\n", buffer[1]);
    if (server_awnser(&*awnser, client) == -1)
        return -1;
    awn_buff = my_str_to_word_array(awnser);
    if (strcmp(awn_buff[0], "301") == 0) {
        if (handle_password_awnser(client, buffer[1]) == -1)
            return -1;
    } else
        create_new_user(buffer, client);
    return 0;
}
