/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** load_thread
*/

#include "../include/prototype.h"
#include "../include/server.h"
#include "data_save.h"

void end_of_load(data_t *data_server, message_s_t pos, int nb_comment)
{
    data_server->teams[pos.team].channels[pos.channel].messages[pos.msg]
    .thread.comment[nb_comment].user_uuid = NULL;
    data_server->teams[pos.team].channels[pos.channel].messages[pos.msg]
    .thread.comment[nb_comment].comment = NULL;
    data_server->teams[pos.team].channels[pos.channel].messages[pos.msg]
    .thread.comment[nb_comment].time_send = 0;
}

void msg_data_find(data_t *data_server, char *token, message_s_t pos)
{
    int nb_comment = nb_comment_in_thread(token);
    char *token_line = strtok(token, "{}");
    int pos_comment = 0;
    char **copy_token_line = malloc(sizeof(char *) * (nb_comment + 1));

    for (int i = 0; i < nb_comment; i++) {
        copy_token_line[i] = strdup(token_line);
        token_line = strtok(NULL, "{}");
    }
    data_server->teams[pos.team].channels[pos.channel].messages[pos.msg]
    .thread.comment = malloc(sizeof(comment_t) * (nb_comment + 2));
    while (nb_comment > pos_comment) {
        msg_data_loop(data_server, copy_token_line[pos_comment], pos,
        pos_comment);
        pos_comment += 1;
    }
    end_of_load(data_server, pos, nb_comment);
}

message_s_t init_pos2(void)
{
    message_s_t pos;

    pos.team = 0;
    pos.channel = 0;
    pos.msg = 0;
    return pos;
}

void process_thread_data(FILE *file, data_t *data_server, int nb_line)
{
    char line[1024];
    char *token = NULL;
    message_s_t pos = init_pos2();

    for (int i = 0; i < nb_line; i++) {
        fgets(line, 1024, file);
        token = strtok(line, "[]");
        pos_in_team(data_server, token, &pos);
        token = strtok(NULL, "[]");
        pos_in_channel(data_server, token, &pos);
        token = strtok(NULL, "[]");
        pos_in_thread(data_server, token, &pos);
        token = strtok(NULL, "[]");
        data_server->teams[pos.team].channels[pos.channel].messages[pos.msg]
        .thread.description = strdup(token);
        token = strtok(NULL, "[]");
        msg_data_find(data_server, token, pos);
    }
}

void load_thread(data_t *data_server)
{
    FILE *file = fopen("data/thread.conf", "rb");
    int nb_line;

    if (file == NULL) {
        printf("Error opening file");
        return;
    }
    nb_line = det_nb_line(file);
    fseek(file, 0, SEEK_SET);
    process_thread_data(file, data_server, nb_line);
    fclose(file);
}
