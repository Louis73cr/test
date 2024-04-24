/*
** EPITECH PROJECT, 2024
** B-NWP-400-PAR-4-1-myteams-louis.croci
** File description:
** handle_pm
*/

#include "../../include/server.h"
#include "../../include/prototype.h"

int pm_commande2(char *buffer, client_fds_t *client_fds, data_t *data_server)
{
    if (strncmp(buffer, "PM_PM ", 6) == 0) {
        get_msg_pm(client_fds, data_server);
        return 0;
    }
    if (strncmp(buffer, "PM_G", 4) == 0) {
        get_pm(client_fds, data_server);
        return 0;
    }
    if (strncmp(buffer, "PM_SM ", 6) == 0) {
        send_msg_pm(buffer + 6, client_fds, data_server);
        return 0;
    }
    return 1;
}

int pm_commande(char *buffer, client_fds_t *client_fds, data_t *data_server)
{
    if (strncmp(buffer, "PM_C ", 5) == 0) {
        create_pm(buffer, client_fds, data_server);
        return 0;
    }
    if (strncmp(buffer, "PM_I", 4) == 0) {
        info_pm(client_fds, data_server);
        return 0;
    }
    if (strncmp(buffer, "PM_MV ", 6) == 0) {
        move_pm(buffer + 6, client_fds, data_server);
        return 0;
    }
    return pm_commande2(buffer, client_fds, data_server);
}
