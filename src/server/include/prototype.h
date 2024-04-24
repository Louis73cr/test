/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** prototype
*/

#include "server.h"
#include "logging_server.h"
#include "../data_save/data_save.h"
#include "../commande/thread/thread.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>

#ifndef PROTOTYPE_H_
    #define PROTOTYPE_H_
    #define EXIT_ERROR_EPITECH 84

//handle_message.c
void handle_message(char *, client_fds_t *, data_t *);
void handle_not_connected_client(char *, client_fds_t *, data_t *);

//uuid_generator.c
char *uuid_generator(void);

//handle_team.c
int team_commande(char *, client_fds_t *, data_t *);
char *find_team_name(char *);
void move_team(char *, client_fds_t *, data_t *);
void leave_team(char *, client_fds_t *, data_t *);
void join_team(char *, client_fds_t *, data_t *);
void info_team(char *, client_fds_t *, data_t *);
void get_team(client_fds_t *, data_t *);
void delete_team(char *, client_fds_t *, data_t *);
void create_team(char *, client_fds_t *, data_t *);
void move_team_reinit(client_fds_t *);
void set_join_team_2(int *, int, data_t *);
void set_join_team(int *, int *, char *, data_t *);
void get_user_in_team(data_t *, client_fds_t *);

//handle_channel.c
int channel_commande(char *, client_fds_t *, data_t *);
void send_msg_channel(client_fds_t *, data_t *, char *);
void move_channel(char *, client_fds_t *, data_t *);
int count_messages(data_t *, int, int);
void get_msg_channel(client_fds_t *, data_t *);
void get_channel(client_fds_t *, data_t *);
team_t *witch_team(client_fds_t *, data_t *);
int find_pos_in_channel(client_fds_t *, data_t *, int);
int find_pos_in_team(client_fds_t *, data_t *);
void delete_channel(char *, client_fds_t *, data_t *);
int count_channels(team_t *);
void create_channel(char *, client_fds_t *, data_t *);
char *find_channel_name(char *);
int count_channels_in_team(data_t *, int);
int print_data2(data_t *, int[], int);
void print_data(data_t *, int[], char *, int[]);
void last_print_get_msg(client_fds_t *, char *, int);
void update_channel(client_fds_t *, team_t *, char *, int[]);
void update_channel_triple(team_t *, int);
int find_position_in_team(client_fds_t *, data_t *);

//handle_pm.c
int pm_commande(char *, client_fds_t *, data_t *);
int find_position_in_pm(client_fds_t *, data_t *);
void info_pm(client_fds_t *, data_t *);
void move_pm(char *, client_fds_t *, data_t *);
void create_pm(char *, client_fds_t *, data_t *);
void get_msg_pm(client_fds_t *, data_t *);
void get_pm(client_fds_t *, data_t *);
void send_msg_pm(char *, client_fds_t *, data_t *);

//handle_thread.c
int thread_commande(char *, client_fds_t *, data_t *);
int find_pos_in_message(client_fds_t *, data_t *, int, int);
int find_pos_in_comment(data_t *, thread_value_t);
void thread_create(char *, client_fds_t *, data_t *);
void thread_get_msg(client_fds_t *, data_t *);
int check_acces(client_fds_t *, data_t *, thread_value_t *);
int check_acces2(client_fds_t *, data_t *, thread_value_t *);
void thread_info(client_fds_t *, data_t *);
void thread_move(char *, client_fds_t *, data_t *);
void thread_send_msg(char *, client_fds_t *, data_t *);
int find_pos_in_message2(client_fds_t *, data_t *, int, int);
//handle_comment.c
void comment_commande(char *, client_fds_t *, data_t *);

//handle_user.c
int user_commande(char *, client_fds_t *, data_t *);
int check_value_username(const char *, user_t *);
bool check_value_password(const char *, user_t *, const char *);
void set_status_client(client_fds_t *, data_t *);

//data_gestions.c
void load_client_data(data_t *);
void save_client_data(data_t *);

//current_time.c
time_t current_time(void);
char *time_t_to_str(time_t);
time_t str_to_time_t(char *);

//channel_save.c
void save_channel(data_t *);
void load_channel(data_t *);
void no_chanell_file(data_t *);
char *pic_data(data_t *, char *, int, int);
int find_team_index_by_channel_uuid(data_t *, char *);
void write_channel_data(FILE *, channel_t, char *);

//team_save.c
void save_team(data_t *);
void load_team(data_t *);
void save_team(data_t *);

//user_save.c
void save_user(data_t *);
void load_user(data_t *);

//nb_line_in_conf_file.c
int det_nb_line(FILE *);

//message_save.c
void save_message(data_t *);
void load_message(data_t *);
void read_msg(data_t *, message_s_t, char *);
int find_channel_index(data_t *, char *, int);
int find_team_index_by_team_uuid(data_t *, char *);
void no_message_file(data_t *);
void load_data_msg(FILE *, data_t *, int);
void write_channel_messages(FILE *, channel_t *);
void write_message(FILE *, message_t *);
void load_message(data_t *);
void no_message(data_t *, int, int);
void no_message_file_2(data_t *, int, int);

//other_commande.c
void other_commande(char *, client_fds_t *);

//server.c
void server_launch(char *);
int create_server_socket(int);
void check_client_data(client_fds_t *, int, data_t *);
void accept_connections(int, client_fds_t *, int *);
void max_file_descriptor_check(int *, int);

//thread_save.c
void save_thread(data_t *);
void load_thread(data_t *);
void msg_data_loop(data_t *, char *, message_s_t, int);
int nb_comment_in_thread(char *);
void pos_in_thread(data_t *, char *, message_s_t *);
void pos_in_channel(data_t *, char *, message_s_t *);
void pos_in_team(data_t *, char *, message_s_t *);

//save_personnal_message.c
void save_personnal_message(data_t *);
void load_personnal_message(data_t *);
int nb_msg_in_pm(char *);
void load_personnal_message_no_file(data_t *);
void load_end_of_pm(data_t *, int);

#endif /* !PROTOTYPE_H_ */
