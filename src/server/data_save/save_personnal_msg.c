/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** save_personnal_msg
*/

#include "../include/server.h"
#include "../include/prototype.h"

void save_personnal_message(data_t *data_server)
{
    FILE *file = fopen("data/personnal_msg.conf", "wb");

    if (file == NULL) {
        printf("Error opening file");
        return;
    }
    for (int i = 0; data_server->personal[i].uuid_mp != NULL; i++) {
        fprintf(file, "[%s][%s][%s][", data_server->personal[i].uuid_mp,
        data_server->personal[i].user_uuid_1, data_server->personal[i]
        .user_uuid_2);
        for (int j = 0; data_server->personal[i].messages[j].message !=
        NULL; j++) {
            fprintf(file, "{(%s)(%s)(%s)}", data_server->personal[i]
            .messages[j].user_uuid,
            data_server->personal[i].messages[j].message,
            time_t_to_str(data_server->personal[i].messages[j].time_send));
        }
        fprintf(file, "]\n");
    }
    fclose(file);
}
