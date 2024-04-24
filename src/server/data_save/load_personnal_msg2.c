/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** load_peresonnal_msg
*/

#include "../include/prototype.h"
#include "../include/server.h"
#include "data_save.h"

void load_personnal_message_no_file(data_t *data_server)
{
    data_server->personal = malloc(sizeof(personal_t) * 2);
    data_server->personal[0].uuid_mp = NULL;
    data_server->personal[0].user_uuid_1 = NULL;
    data_server->personal[0].user_uuid_2 = NULL;
    data_server->personal[0].messages = malloc(sizeof(message_t) * 2);
    data_server->personal[0].messages[0].message = NULL;
    data_server->personal[0].messages[0].user_uuid = NULL;
    data_server->personal[0].messages[0].time_send = 0;
}

int nb_msg_in_pm(char *token)
{
    int nb_comment = 0;

    for (int i = 0; token[i] != '\0'; i++) {
        if (token[i] == '{')
            nb_comment += 1;
    }
    return nb_comment;
}

void load_end_of_pm(data_t *data_server, int nb_line)
{
    data_server->personal[nb_line].uuid_mp = NULL;
    data_server->personal[nb_line].user_uuid_1 = NULL;
    data_server->personal[nb_line].user_uuid_2 = NULL;
    data_server->personal[nb_line].messages = malloc(sizeof(message_t) * 2);
    data_server->personal[nb_line].messages[0].message = NULL;
    data_server->personal[nb_line].messages[0].user_uuid = NULL;
    data_server->personal[nb_line].messages[0].time_send = 0;
}
