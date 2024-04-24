/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** list_thread
*/

#include "../../../../include/client.h"

int display_thread(char **buff, char const *thread_uuid)
{
    client_channel_print_threads(thread_uuid, buff[1], (time_t)buff[2],
    buff[3], buff[4]);
    return 0;
}

int get_thread_info(char const *thread_uuid, client_t *client)
{
    char awnser[BUF_SIZE];
    char **buff = NULL;

    dprintf(client->con.socket, "THREAD_I %s\t\n", thread_uuid);
    if (server_awnser(&*awnser, client) == -1) {
        return -1;
    }
    buff = my_str_to_word_array(awnser);
    display_thread(buff, thread_uuid);
    free_array(buff);
    return 0;
}

int parse_threads(char **buffer, client_t *client)
{
    int b_size = get_buffer_size(buffer);

    if (b_size < 2) {
        return -1;
    }
    for (int i = 1; i < b_size; i++) {
        if (strcmp(buffer[i], ",") != 0) {
            get_thread_info(buffer[i], client);
        }
    }
    return 0;
}

int show_all_thread(char **buffer, client_t *client)
{
    char awnser[BUF_SIZE];
    char **buff = NULL;

    if (get_buffer_size(buffer) != 1) {
        return -1;
    }
    dprintf(client->con.socket, "THREAD_G\t\n");
    if (server_awnser(&*awnser, client) == -1) {
        return -1;
    }
    buff = my_str_to_word_array(awnser);
    if (strcmp(buff[0], "200") == 0) {
        parse_threads(buff, client);
    } else {
        printf("%s", awnser);
    }
    free_array(buff);
    return 0;
}
