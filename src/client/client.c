/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** client
*/

#include "../../include/include.h"
#include "../../include/client.h"

int client_help(void)
{
    printf("USAGE: ./myteams_cli ip port\n\t");
    printf("ip   is the server ip address on which the server socket listen");
    printf("\n\tport is the port number on which the server socket listen\n");
    return 0;
}

void message_exit(const char *str)
{
    printf("%s\n", str);
    exit(FAILURE);
}

void init_client(client_t *client, const char **args)
{
    client->con.socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client->con.socket == -1)
        message_exit("Error while setting client socket. Exiting");
    client->con.serv_addr.sin_family = AF_INET;
    client->con.serv_addr.sin_addr.s_addr = inet_addr(args[1]);
    client->con.serv_addr.sin_port = htons(atoi(args[2]));
    return;
}

client_t setup_client_struct(client_t client)
{
    client.loc.channel_uuid = NULL;
    client.loc.team_uuid = NULL;
    client.loc.thread_uuid = NULL;
    client.loc.pm_uuid = NULL;
    client.user.name = NULL;
    client.user.uuid = NULL;
    return client;
}

int main(int ac, char **av)
{
    client_t client = setup_client_struct(client);

    if (strcmp(av[1], "-help") == 0)
        return client_help();
    if (ac != 3)
        return FAILURE;
    init_client(&client, (const char **)av);
    if (connect(client.con.socket, (struct sockaddr *)&client.con.serv_addr,
    sizeof(client.con.serv_addr)) == -1)
        message_exit("Error, can't connect to server. Exiting");
    run_client(&client);
    close(client.con.socket);
    return EXIT_SUCCESS;
}
