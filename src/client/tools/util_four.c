/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** util_four
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int is_non_alphanum(char const c)
{
    if (c == '-' || c == '/' || c == ',' || c == '_')
        return 0;
    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
        return 0;
    } else if ((c >= '0' && c <= '9') || c == '=' || c == '?') {
        return 0;
    } else {
        return 1;
    }
}

static int is_char_before_alphanum(int nb, int i, char const *str)
{
    if (i > 0 && is_non_alphanum(str[i - 1]) != 1) {
        nb += 1;
    }
    return nb;
}

static int get_number_word(char const *str)
{
    int i = 0;
    int nb = 0;

    while (str[i] != '\0') {
        if (is_non_alphanum(str[i]) == 1) {
            nb = is_char_before_alphanum(nb, i, str);
        }
        i += 1;
    }
    return nb;
}

static char **put_words_in_array(char **arr, char const *str)
{
    int i = 0;
    int curr_word = 0;
    int curr_ch = 0;

    while (str[i] != '\0') {
        if (is_non_alphanum(str[i]) != 1) {
            arr[curr_word][curr_ch] = str[i];
            curr_ch += 1;
        }
        if (i != 0 && is_non_alphanum(str[i - 1]) != 1 &&
        is_non_alphanum(str[i]) == 1) {
            arr[curr_word][curr_ch] = '\0';
            curr_word += 1;
            curr_ch = 0;
        }
        i += 1;
    }
    return arr;
}

char **my_str_to_word_array(char const *str)
{
    int nb_words = get_number_word(str);
    char **arr = NULL;

    arr = malloc(sizeof(char *) * (nb_words + 2));
    for (int i = 0; i < nb_words + 1; i++) {
        arr[i] = calloc(40, sizeof(char));
    }
    arr[nb_words + 1] = NULL;
    arr = put_words_in_array(arr, str);
    return arr;
}
