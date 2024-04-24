/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** util_three
*/

#include "../../../include/client.h"

int analyze_line(char *line, char *user_uuid)
{
    char *token = strtok(line, "[]\n");

    while (token != NULL) {
        if (strcmp(token, user_uuid) == 0) {
            return 1;
        }
        token = strtok(NULL, "[]\n");
    }
    return 0;
}

int parse_pm(char *user_uuid)
{
    int idx = 0;
    FILE *file = fopen("data/personnal_msg.conf", "r");
    char *line = NULL;
    size_t line_length = 0;

    if (file == NULL)
        return -1;
    while (getline(&line, &line_length, file) != -1) {
        if (analyze_line(line, user_uuid) == 1) {
            free(line);
            fclose(file);
            return idx;
        }
        idx++;
    }
    free(line);
    fclose(file);
    return -1;
}
