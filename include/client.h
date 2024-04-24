/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** client
*/

#include "include.h"
#include "../libs/myteams/logging_client.h"

#ifndef CLIENT_H_
    #define CLIENT_H_

    #include <dlfcn.h>
    #include <sys/select.h>

    #define BUF_SIZE 1024
    #define DISCONNECT 12
    #define USER_NOT_FOUND -12
    #define STDIN 0
    #define FAILURE 84

typedef struct connection_s {
    int socket;
    struct sockaddr_in serv_addr;
} connection_t;

typedef struct user_s {
    char *name;
    char *uuid;
} user_t;

typedef struct location_s {
    char *team_uuid;
    char *channel_uuid;
    char *thread_uuid;
    char *pm_uuid;
} loc_t;

typedef struct select_s {
    fd_set readfds;
    int server_fd;
    int max_fd;
} select_t;

typedef struct client_s {
    user_t user;
    loc_t loc;
    connection_t con;
} client_t;

typedef struct client_loop_s {
    int isLooping;
    char input[BUF_SIZE];
    char **buffer;
    int server_fd;
    int max_fd;
} client_loop_t;

typedef struct str_array_s {
    int nb_word;
    int word_start;
    int in_quote;
} str_array_t;

//util
char **my_str_to_word_array(char const *str);
char **my_str_to_word_array_input(char const *str);

//util_bis
int get_buffer_size(char **buffer);
int free_array(char **array);
int user_position_index(client_t *client);
int server_awnser(char *awn, client_t *client);

//handle_list
int handle_list(char **buffer, client_t *client);
int show_all_channels(char **buffer, client_t *client);
int show_all_teams(char **buffer, client_t *client);
int show_all_thread(char **buffer, client_t *client);
int show_all_response(char **buffer, client_t *client);
int parse_teams(char **buff, client_t *client);

//handle_use
int handle_use(char **buffer, client_t *client);
int set_new_teams(char **buffer, client_t *client);
int set_team_channel(char **buffer, client_t *client);
int set_all(char **buffer, client_t *client);

//client_run
int run_client(client_t *client);

//handle_logout
int handle_logout(char **buffer, client_t *client);

//handle_login
int handle_login(char **buffer, client_t *client);
int create_new_user(char **buffer, client_t *client);
int last_check(client_t *client);

//handle_create
int handle_create(char **buffer, client_t *client);
int create_team(char **buffer, client_t *client);
int create_thread(char **buffer, client_t *client);
int create_channel(char **buffer, client_t *client);
int create_response(char **buffer, client_t *client);

//handle_help
int handle_help(void);

//handle_subscribe
int handle_subscribe(char **buffer, client_t *client);

//handle_unsubscribe
int handle_unsubscribe(char **buffer, client_t *client);

//handle_subscribed
int handle_subscribed(char **buffer, client_t *client);

//handle_users
int handle_users(char **buffer, client_t *client);

//handle_user
int handle_user(char **buffer, client_t *client);

//handle_info
int handle_info(char **buffer, client_t *client);

//handle_send
int handle_send(char **buffer, client_t *client);
int parse_pm(char *user_uuid);
int find_pm_user(char **buffer, client_t *client, char **buff);
int move_into_pm(char *pm_uuid, client_t *client);

//handle_message
int handle_message(char **buffer, client_t *client);

#endif /* !CLIENT_H_ */
