/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** data_gestion
*/

#include "../include/server.h"
#include "../include/prototype.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void save_client_data(data_t *data_server)
{
    save_user(data_server);
    save_team(data_server);
    save_channel(data_server);
    save_message(data_server);
    save_thread(data_server);
    save_personnal_message(data_server);
}

void load_client_data(data_t *data_server)
{
    load_user(data_server);
    load_team(data_server);
    load_channel(data_server);
    load_message(data_server);
    load_thread(data_server);
    load_personnal_message(data_server);
}
