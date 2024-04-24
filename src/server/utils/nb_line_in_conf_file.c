/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** nb_lin_in_conf_file
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int det_nb_line(FILE *file)
{
    int nb_users = 0;

    for (char ch; (ch = fgetc(file)) != EOF;) {
        if (ch == '\n') {
            nb_users++;
        }
    }
    return nb_users;
}
