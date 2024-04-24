/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** save_thread
*/

#include "../include/server.h"
#include "../include/prototype.h"

void save_thread_suite(FILE *file, data_t *data_server, int i, int j)
{
    for (int k = 0; data_server->teams[i].channels[j].messages[k].
    thread.thread_uuid != NULL; k++) {
        fprintf(file, "[%s][%s][", data_server->teams[i].channels[j].
        messages[k].thread.thread_uuid, data_server->teams[i].channels[j]
        .messages[k].thread.description);
        for (int l = 0; data_server->teams[i].channels[j].messages[k].
        thread.comment[l].user_uuid != NULL; l++) {
            fprintf(file, "{(%s)(%s)(%s)}", data_server->teams[i].channels[j]
            .messages[k].thread.comment[l].user_uuid, data_server->teams[i]
            .channels[j].messages[k].thread.comment[l].comment,
            time_t_to_str(data_server->teams[i].channels[j].messages[k]
            .thread.comment[l].time_send));
        }
        fprintf(file, "]\n");
    }
}

void save_thread(data_t *data_server)
{
    FILE *file = fopen("data/thread.conf", "wb");

    if (file == NULL) {
        printf("Error opening file");
        return;
    }
    for (int i = 0; data_server->teams[i].team_uuid != NULL; i++) {
        for (int j = 0; data_server->teams[i].channels[j].channel_uuid
        != NULL; j++) {
            fprintf(file, "[%s][%s]", data_server->teams[i].team_uuid,
            data_server->teams[i].channels[j].channel_uuid);
            save_thread_suite(file, data_server, i, j);
        }
    }
    fclose(file);
}
