/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** handle_use
*/

#include "../../../../include/include.h"
#include "../../../../include/client.h"

int set_default_location(client_t *client)
{
    char awn[BUF_SIZE];
    char **buff = NULL;

    dprintf(client->con.socket, "TEAM_R\t\n");
    if (server_awnser(&*awn, client) == -1) {
        return -1;
    }
    buff = my_str_to_word_array(awn);
    if (strcmp(buff[0], "200") != 0) {
        free_array(buff);
        return -1;
    }
    client->loc.channel_uuid = NULL;
    client->loc.team_uuid = NULL;
    client->loc.thread_uuid = NULL;
    free_array(buff);
    return 0;
}

int move_user(client_t *client, char **buffer)
{
    int b_size = get_buffer_size(buffer);

    if (b_size == 2) {
        set_new_teams(buffer, client);
    }
    if (b_size == 3) {
        set_team_channel(buffer, client);
    }
    if (b_size == 4) {
        set_all(buffer, client);
    }
    return 0;
}

int handle_use(char **buffer, client_t *client)
{
    if (get_buffer_size(buffer) == 1) {
        set_default_location(client);
    } else if (get_buffer_size(buffer) > 1) {
        move_user(client, buffer);
    }
    return 0;
}
