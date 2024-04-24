/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** help
*/

#include "../../../../include/client.h"

int handle_help(void)
{
    printf("MY TEAMS - HELP\n\tthe following commands are available:\n");
    printf("/help, /login [user], /logout, /users, /user [user_id], ");
    printf("/send [user_id] [message], /message [user_id], /subscribe ");
    printf("[team_id], /subscribed [team_id], /unsubscribe [team_id], ");
    printf("/use [team_id] [channel_id] [thread_id], /create, /list, /info\n");
    return 0;
}
