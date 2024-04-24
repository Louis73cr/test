/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** util
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../include/client.h"

void remove_quotes(char **word)
{
    int len = 0;

    for (int i = 0; word[i] != NULL; i++) {
        len = strlen(word[i]);
        if (len >= 2 && word[i][0] == '"' && word[i][len - 1] == '"') {
            memmove(word[i], word[i] + 1, len - 2);
            word[i][len - 2] = '\0';
        }
    }
}

char **word_in_array(char **word, int i, str_array_t *arr, char const *str)
{
    int word_len = i - arr->word_start;

    if (word_len > 0) {
        word = realloc(word, sizeof(char *) * (arr->nb_word + 1));
        word[arr->nb_word] = malloc(sizeof(char) * (word_len + 1));
        strncpy(word[arr->nb_word], str + arr->word_start, word_len);
        word[arr->nb_word][word_len] = '\0';
        arr->nb_word += 1;
    }
    return word;
}

char **my_str_to_word_array_input(char const *str)
{
    int str_len = strlen(str);
    char **word = NULL;
    str_array_t arr = {0,0,0};

    for (int i = 0; i <= str_len; i++) {
        if (str[i] == '"' && (i == 0 || str[i - 1] != '\\'))
            arr.in_quote = !arr.in_quote;
        if ((str[i] == ' ' || str[i] == '\0') && !arr.in_quote) {
            word = word_in_array(word, i, &arr, str);
            arr.word_start = i + 1;
        }
    }
    word = realloc(word, sizeof(char *) * (arr.nb_word + 1));
    word[arr.nb_word] = NULL;
    remove_quotes(word);
    return word;
}
