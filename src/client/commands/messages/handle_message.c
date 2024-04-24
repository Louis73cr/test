/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** handle_message
*/

#include "../../../../include/client.h"

time_t convert_to_time(char *date, char *hour, char *min, char *sec)
{
    struct tm tm_time;
    time_t time;

    memset(&tm_time, 0, sizeof(struct tm));
    sscanf(date, "%d-%d-%d", &tm_time.tm_year, &tm_time.tm_mon,
    &tm_time.tm_mday);
    tm_time.tm_year -= 1900;
    tm_time.tm_mon -= 1;
    sscanf(hour, "%d", &tm_time.tm_hour);
    sscanf(min, "%d", &tm_time.tm_min);
    sscanf(sec, "%d", &tm_time.tm_sec);
    time = mktime(&tm_time);
    return time;
}

int print_pm(char **buff, int i)
{
    time_t time = convert_to_time(buff[i + 2], buff[i + 3], buff[i + 4],
    buff[i + 5]);

    client_private_message_print_messages(buff[i], time, buff[i + 1]);
    return 0;
}

int get_pm(char **buff)
{
    int b_size = get_buffer_size(buff);

    if (b_size < 2) {
        return -1;
    }
    for (int i = 1; i < b_size - 1; i++) {
        print_pm(buff, i);
        i += 6;
    }
    return 0;
}

int display_pm(client_t *client)
{
    char awn[BUF_SIZE];
    char **buff = NULL;

    dprintf(client->con.socket, "PM_PM %s\t\n", client->loc.pm_uuid);
    printf("%s\n", client->loc.pm_uuid);
    if (server_awnser(&*awn, client) == -1) {
        return -1;
    }
    buff = my_str_to_word_array(awn);
    if (strcmp(buff[0], "200") == 0) {
        get_pm(buff);
    }
    return 0;
}

int handle_message(char **buffer, client_t *client)
{
    char awn[BUF_SIZE];
    char **buff = NULL;

    if (get_buffer_size(buffer) != 2) {
        return -1;
    }
    dprintf(client->con.socket, "PM_G\t\n");
    if (server_awnser(&*awn, client) == -1) {
        return -1;
    }
    buff = my_str_to_word_array(awn);
    if (strcmp(buff[0], "200") == 0) {
        find_pm_user(buffer, client, buff);
        display_pm(client);
    }
    free_array(buff);
    return 0;
}
