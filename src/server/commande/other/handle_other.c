/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** other_command
*/

#include "../../include/server.h"

void other_commande(char *buffer, client_fds_t *client_fds)
{
    if (strncmp(buffer, "HELP", 4) == 0) {
        dprintf(client_fds->server_fd, "200 Success\n");
        return;
    }
    if (strncmp(buffer, "INFO", 4) == 0) {
        dprintf(client_fds->server_fd, "200 Success\n");
        return;
    }
    dprintf(client_fds->server_fd, "500 Error\n");
}
