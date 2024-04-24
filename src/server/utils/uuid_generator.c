/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** uuid_generator
*/

#include <stdio.h>
#include <uuid/uuid.h>
#include <stdlib.h>

char *uuid_generator(void)
{
    uuid_t uuid;
    char *uuid_str = malloc(sizeof(char) * 37);

    uuid_generate_random(uuid);
    uuid_unparse(uuid, uuid_str);
    return uuid_str;
}
