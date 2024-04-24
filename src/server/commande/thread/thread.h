/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** thread
*/

#ifndef THREAD_H_
    #define THREAD_H_

typedef struct thread_value_t {
    int pos_in_team;
    int pos_in_channel;
    int pos_in_msg;
    int pos_in_comment;
    int name_len;
} thread_value_t;

#endif /* !THREAD_H_ */
