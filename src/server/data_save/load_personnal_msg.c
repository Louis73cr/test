/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** load_peresonnal_msg
*/

#include "../include/prototype.h"
#include "../include/server.h"
#include "data_save.h"

void msg_data_loop_pm(data_t *data_server, char *token_line, int i,
    int pos_comment)
{
    char *copy_token_line = strdup(token_line);
    char *token_msg = strtok(copy_token_line, "()");

    data_server->personal[i].messages[pos_comment].user_uuid =
    strdup(token_msg);
    token_msg = strtok(NULL, "()");
    data_server->personal[i].messages[pos_comment].message =
    strdup(token_msg);
    token_msg = strtok(NULL, "()");
    data_server->personal[i].messages[pos_comment].time_send =
    str_to_time_t(token_msg);
    free(copy_token_line);
}

void end_of_load_pm(data_t *data_server, int i, int nb_comment)
{
    data_server->personal[i].messages[nb_comment].user_uuid = NULL;
    data_server->personal[i].messages[nb_comment].message = NULL;
    data_server->personal[i].messages[nb_comment].time_send = 0;
}

void msg_data_find_pm(data_t *data_server, char *token, int i)
{
    int nb_comment = nb_msg_in_pm(token);
    char *token_line = strtok(token, "{}");
    int pos_comment = 0;
    char **copy_token_line = malloc(sizeof(char *) * (nb_comment + 1));

    for (int i = 0; i < nb_comment; i++) {
        copy_token_line[i] = strdup(token_line);
        token_line = strtok(NULL, "{}");
    }
    data_server->personal[i].messages = malloc(sizeof(message_t) *
    (nb_comment + 2));
    while (nb_comment > pos_comment) {
        msg_data_loop_pm(data_server, copy_token_line[pos_comment], i,
        pos_comment);
        pos_comment += 1;
    }
    end_of_load_pm(data_server, i, nb_comment);
}

void process_pm_data(FILE *file, data_t *data_server, int nb_line)
{
    char line[1024];
    char *token = NULL;

    data_server->personal = malloc(sizeof(personal_t) * (nb_line + 2));
    for (int i = 0; i < nb_line; i++) {
        fgets(line, 1024, file);
        token = strtok(line, "[]");
        data_server->personal[i].uuid_mp = strdup(token);
        token = strtok(NULL, "[]");
        data_server->personal[i].user_uuid_1 = strdup(token);
        token = strtok(NULL, "[]");
        data_server->personal[i].user_uuid_2 = strdup(token);
        token = strtok(NULL, "[]");
        msg_data_find_pm(data_server, token, i);
    }
    load_end_of_pm(data_server, nb_line);
}

void load_personnal_message(data_t *data_server)
{
    FILE *file = fopen("data/personnal_msg.conf", "rb");
    int nb_line;

    if (file == NULL) {
        load_personnal_message_no_file(data_server);
        return;
    }
    nb_line = det_nb_line(file);
    fseek(file, 0, SEEK_SET);
    process_pm_data(file, data_server, nb_line);
    fclose(file);
}
