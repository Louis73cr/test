/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** client_run
*/

#include "../../include/include.h"
#include "../../include/client.h"

int handle_command(char **buffer, client_t *client)
{
    int (*functions[])(char **, client_t *) = {handle_login, handle_logout,
    handle_use, handle_list, handle_subscribe, handle_create,
    handle_unsubscribe, handle_subscribed, handle_users, handle_user,
    handle_info, handle_send, handle_message};
    const char *commands[] = {"/login", "/logout", "/use", "/list",
    "/subscribe", "/create", "/unsubscribe", "/subscribed",
    "/users", "/user", "/info", "/send", "/messages"};
    int return_val = 0;
    long unsigned int i = 0;

    for (i = 0; i < sizeof(commands) / sizeof(commands[0]); i++) {
        if (strcmp(buffer[0], commands[i]) == 0) {
            return_val = functions[i](buffer, client);
            break;
        }
    }
    if (return_val == DISCONNECT)
        return -1;
    return 0;
}

int handle_user_input(client_loop_t *loop, client_t *client)
{
    ssize_t size;

    size = read(0, loop->input, BUF_SIZE);
    if (size == -1) {
        printf("ERROR\n");
        return -1;
    }
    loop->input[size - 1] = '\0';
    loop->buffer = my_str_to_word_array_input(loop->input);
    if (strcmp(loop->buffer[0], "/help") == 0)
        handle_help();
    if (handle_command(loop->buffer, client) == -1)
        loop->isLooping = 0;
    return 0;
}

int handle_server_messages(client_loop_t *loop)
{
    char buffer[BUF_SIZE];
    ssize_t bytes_received = recv(loop->server_fd, buffer, sizeof(buffer), 0);

    if (bytes_received < 0) {
        printf("error while receiving from server\n");
        exit(FAILURE);
    } else if (bytes_received == 0) {
        printf("Server disconnected.\n");
        loop->isLooping = 0;
        return -1;
    } else {
        printf("You received a message!\n");
    }
    return 0;
}

int run_client(client_t *client)
{
    client_loop_t loop;
    fd_set readfds;

    loop.server_fd = client->con.socket;
    loop.isLooping = 1;
    while (loop.isLooping == 1) {
        FD_ZERO(&readfds);
        FD_SET(loop.server_fd, &readfds);
        FD_SET(STDIN, &readfds);
        write(1, "$> ", 4);
        if (select(loop.server_fd + 1, &readfds, NULL, NULL, NULL) < 0) {
            printf("select error");
            exit(FAILURE);
        }
        if (FD_ISSET(STDIN, &readfds))
            handle_user_input(&loop, client);
        if (FD_ISSET(loop.server_fd, &readfds))
            handle_server_messages(&loop);
    }
    return 0;
}
