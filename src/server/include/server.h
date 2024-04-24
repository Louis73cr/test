/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** server
*/


#ifndef SERVER_H_
    #define SERVER_H_

    #include "logging_server.h"
    #include <stdio.h>
    #include <stdlib.h>
    #include <stdbool.h>
    #include <string.h>
    #include <uuid/uuid.h>
    #include <time.h>

    #define MAX_NAME_LENGTH 32
    #define MAX_DESCRIPTION_LENGTH 255
    #define MAX_BODY_LENGTH 512
    #define MAX_CLIENTS 10
    #define BUF_SIZE 1024
    #define UUID_LENGTH 37

typedef enum is_connected_t {
    NOT_CONNECTED,
    CONNECTION_IN_PROGRESS,
    CONNECTED
} is_connected_t;

typedef struct client_conection_t {
    int server_fd;
    is_connected_t is_connected;
    char *client_uuid;
} client_conection_t;

typedef struct client_fds_t {
    int server_fd;
    int is_connected;
    char *client_uuid;
    char *uuid_in_team;
    char *uuid_in_channel;
    char *uuid_in_thread;
    char *uuid_in_mp;
} client_fds_t;

typedef struct user_t {
    char *user_uuid;
    char *username;
    char *password;
    is_connected_t status;
} user_t;

typedef struct comment_t {
    char *user_uuid;
    char *comment;
    time_t time_send;
} comment_t;

typedef struct thread_t {
    char *thread_uuid;
    char *title;
    char *description;
    time_t time_send;
    comment_t *comment;
} thread_t;

typedef struct message_t {
    char *message;
    char *user_uuid;
    time_t time_send;
    thread_t thread;
} message_t;

typedef struct channel_t {
    char *channel_uuid;
    char *channel_name;
    char *channel_description;
    char **user_uuid;
    message_t *messages;
} channel_t;

typedef struct team_t {
    char *team_uuid;
    char *team_name;
    char *team_description;
    char **user_uuid;
    struct channel_t *channels;
} team_t;

typedef struct personal_t {
    char *user_uuid_1;
    char *user_uuid_2;
    char *uuid_mp;
    message_t *messages;
} personal_t;

typedef struct data_s {
    struct team_t *teams;
    struct user_t *users;
    struct personal_t *personal;
} data_t;

#endif /* !SERVER_H_ */
