/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** list_response
*/

#include "../../../../include/client.h"

int display_messages(char **buff, int i, client_t *client)
{
    client_thread_print_replies(client->loc.thread_uuid, buff[i + 1],
    (time_t)buff[i + 3], buff[i + 2]);
    return 0;
}

int parse_response(char **buff, client_t *client)
{
    int b_size = get_buffer_size(buff);

    if (b_size < 2) {
        return -1;
    }
    for (int i = 1; i < b_size; i++) {
        display_messages(buff, i, client);
        i += 4;
    }
    return 0;
}

int show_all_response(char **buffer, client_t *client)
{
    char awnser[BUF_SIZE];
    char **buff = NULL;

    if (get_buffer_size(buffer) != 1) {
        return -1;
    }
    dprintf(client->con.socket, "THREAD_GM %s\t\n", client->loc.thread_uuid);
    if (server_awnser(&*awnser, client) == -1) {
        return -1;
    }
    buff = my_str_to_word_array(awnser);
    if (parse_response(buff, client) == -1) {
        free_array(buff);
        return -1;
    }
    free_array(buff);
    return 0;
}
