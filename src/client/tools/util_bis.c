/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** util_bis
*/

#include <stdio.h>
#include <stdlib.h>
#include "../../../include/client.h"

int get_buffer_size(char **buffer)
{
    int i = 0;

    while (buffer[i] != NULL) {
        i += 1;
    }
    return i;
}

int free_array(char **array)
{
    for (int i = 0; array[i] != NULL; i++) {
        free(array[i]);
    }
    free(array);
    return 0;
}

int user_position_index(client_t *client)
{
    if (client->loc.team_uuid == NULL) {
        return 0;
    }
    if (client->loc.channel_uuid == NULL) {
        return 1;
    }
    if (client->loc.thread_uuid == NULL) {
        return 2;
    }
    return 3;
}

int server_awnser(char *awn, client_t *client)
{
    ssize_t size = 0;

    size = read(client->con.socket, awn, BUF_SIZE);
    if (size == -1) {
        printf("Error while receiving from server\n");
        return -1;
    }
    awn[size] = '\0';
    return 0;
}
