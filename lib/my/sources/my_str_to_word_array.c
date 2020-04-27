/*
** EPITECH PROJECT, 2019
** my_str_to_word_array
** File description:
** task4 day8
*/

#include <stdlib.h>
#include "../includes/my.h"

static char *my_specndup(char const *str, int nb)
{
    char *ret = malloc(sizeof(char) * (nb + 1));

    if (!ret)
        return (NULL);
    for (int i = 0; i < nb && str[i] != '\0'; i++)
        ret[i] = str[i];
    ret[nb] = '\0';
    return (ret);
}

char **my_str_to_word_array(char const *str)
{
    int size = my_strlen(str);
    char **ret = malloc(sizeof(char *) * size);
    char const *ptr = str;
    int ret_inc = 0;
    char *new;

    for (int i = 0, inc = 1; i <= size; i++, inc++) {
        if (str[i] >= 33 && str[i] <= 126)
            continue;
        if (inc == 1) {
            ptr = str + i + 1;
            inc = 0;
            continue;
        }
        new = my_specndup(ptr, inc - 1);
        ret[ret_inc++] = new;
        ptr = str + i + 1;
        inc = 0;
    }
    ret[ret_inc] = NULL;
    return (ret);
}