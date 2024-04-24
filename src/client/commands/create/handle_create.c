/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** handle_create
*/

#include "../../../../include/include.h"
#include "../../../../include/client.h"

int handle_create(char **buffer, client_t *client)
{
    int idx = user_position_index(client);

    if (idx == 0)
        create_team(buffer, client);
    if (idx == 1)
        create_channel(buffer, client);
    if (idx == 2)
        create_thread(buffer, client);
    if (idx == 3)
        create_response(buffer, client);
    return 0;
}
