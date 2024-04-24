/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** current_time
*/

#include <time.h>
#include <stdlib.h>
#include <stdio.h>

time_t current_time(void)
{
    time_t c_time;

    time(&c_time);
    return c_time;
}

char *time_t_to_str(time_t timestamp)
{
    struct tm *timeinfo;
    char *tm_str = (char *)malloc(100 * sizeof(char));

    timeinfo = localtime(&timestamp);
    strftime(tm_str, 100, "%Y-%m-%d %H:%M:%S", timeinfo);
    return tm_str;
}

time_t str_to_time_t(const char *str)
{
    struct tm tm = {0};
    time_t time;

    sscanf(str, "%d-%d-%d %d:%d:%d", &tm.tm_year, &tm.tm_mon, &tm.tm_mday,
    &tm.tm_hour, &tm.tm_min, &tm.tm_sec);
    tm.tm_year -= 1900;
    tm.tm_mon -= 1;
    time = mktime(&tm);
    time -= 3600;
    return time;
}
