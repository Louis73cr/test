/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** handle_send
*/

#include "../../../../include/client.h"

int create_new_pm(char **buffer, client_t *client)
{
    char awn[BUF_SIZE];
    char **buff = NULL;

    if (get_buffer_size(buffer) != 3)
        return -1;
    dprintf(client->con.socket, "PM_C %s\t\n", buffer[1]);
    if (server_awnser(&*awn, client) == -1) {
        return -1;
    }
    buff = my_str_to_word_array(awn);
    if (strcmp(buff[0], "200") == 0) {
        client->loc.pm_uuid = buff[1];
    } else {
        free_array(buff);
        client_error_unknown_user(buffer[1]);
    }
    free_array(buff);
    return 0;
}

int move_into_pm(char *pm_uuid, client_t *client)
{
    char awn[BUF_SIZE];
    char **buff = NULL;

    dprintf(client->con.socket, "PM_MV %s\t\n", pm_uuid);
    if (server_awnser(&*awn, client) == -1) {
        return -1;
    }
    buff = my_str_to_word_array(awn);
    if (strcmp(buff[0], "200") == 0) {
        client->loc.pm_uuid = pm_uuid;
    }
    free_array(buff);
    return 0;
}

int find_pm_user(char **buffer, client_t *client, char **buff)
{
    int idx = 0;

    idx = parse_pm(buffer[1]);
    if (idx == -1) {
        client_error_unknown_user(buffer[1]);
        return -1;
    }
    move_into_pm(buff[idx + 1], client);
    return 0;
}

int send_pm(client_t *client, char const *message)
{
    char awn[BUF_SIZE];
    char **buff = NULL;

    dprintf(client->con.socket, "PM_SM %s\t\n", message);
    if (server_awnser(&*awn, client) == -1) {
        return -1;
    }
    buff = my_str_to_word_array(awn);
    if (strcmp(buff[0], "200") != 0) {
        free_array(buff);
        return -1;
    }
    free_array(buff);
    return 0;
}

int handle_send(char **buffer, client_t *client)
{
    char awn[BUF_SIZE];
    char **buff = NULL;

    if (get_buffer_size(buffer) != 3) {
        return -1;
    }
    dprintf(client->con.socket, "PM_G\t\n");
    if (server_awnser(&*awn, client) == -1) {
        return -1;
    }
    buff = my_str_to_word_array(awn);
    if (strcmp(buff[0], "200") == 0) {
        find_pm_user(buffer, client, buff);
        send_pm(client, buffer[2]);
    } else if (strcmp(buff[0], "404") == 0) {
        create_new_pm(buffer, client);
    }
    return 0;
}
