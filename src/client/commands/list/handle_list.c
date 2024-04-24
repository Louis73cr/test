/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** handle_list
*/

#include "../../../../include/include.h"
#include "../../../../include/client.h"

int handle_list(char **buffer, client_t *client)
{
    int user_p = user_position_index(client);

    if (user_p == 0)
        show_all_teams(buffer, client);
    if (user_p == 1)
        show_all_channels(buffer, client);
    if (user_p == 2)
        show_all_thread(buffer, client);
    if (user_p == 3)
        show_all_response(buffer, client);
    return 0;
}
