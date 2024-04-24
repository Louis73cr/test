/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** main
*/

#include "include/prototype.h"

int main(int ac, char **av)
{
    if (ac != 2) {
        printf("Usage: ./myteams_server port\n");
        exit(EXIT_ERROR_EPITECH);
    } else
        server_launch(av[1]);
    return 0;
}
