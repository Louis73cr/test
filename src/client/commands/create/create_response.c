/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** create_response
*/

#include "../../../../include/client.h"

int cr_response_server(char **buffer, client_t *client)
{
    char awnser[BUF_SIZE];
    char **buff = NULL;

    dprintf(client->con.socket, "THREAD_SM %s\t\n", buffer[1]);
    if (server_awnser(&*awnser, client) == -1) {
        return -1;
    }
    buff = my_str_to_word_array(awnser);
    if (strcmp(buff[0], "200") == 0) {
        client_event_thread_reply_received(client->loc.team_uuid,
        client->loc.thread_uuid, client->user.uuid, buffer[1]);
        free_array(buff);
    } else {
        free_array(buff);
        return -1;
    }
    return 0;
}

int create_response(char **buffer, client_t *client)
{
    if (get_buffer_size(buffer) != 2) {
        return -1;
    }
    if (cr_response_server(buffer, client) == -1) {
        dprintf(2, "Error while sending response. Please try again.\n");
    }
    return 0;
}
