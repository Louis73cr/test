/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** create_thread
*/

#include "../../../../include/client.h"

int cr_thread_server(char **buffer, client_t *client)
{
    char awnser[BUF_SIZE];
    char **buff = NULL;
    time_t curr_time;

    dprintf(client->con.socket, "THREAD_C %s0%s %s\t\n", buffer[1], buffer[2],
    client->user.uuid);
    if (server_awnser(&*awnser, client) == -1)
        return -1;
    buff = my_str_to_word_array(awnser);
    if (strcmp(buff[0], "200") == 0) {
        curr_time = time(NULL);
        client_event_thread_created(buff[1], client->user.uuid, curr_time,
        buffer[1], buffer[2]);
        free_array(buff);
    } else {
        free_array(buff);
        return -1;
    }
    return 0;
}

int create_thread(char **buffer, client_t *client)
{
    if (get_buffer_size(buffer) != 3) {
        return -1;
    }
    if (cr_thread_server(buffer, client) == -1) {
        dprintf(2, "Error, while creating thread. Please try again.\n");
    }
    return 0;
}
