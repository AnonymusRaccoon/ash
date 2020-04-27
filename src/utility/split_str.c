/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** split_str
*/

#include <malloc.h>
#include <stddef.h>
#include "my.h"

int count_char(char *str, char c)
{
    int count = 0;

    while (*(str++))
        if (*str == c)
            count++;
    return (count);
}

int count_str(char *str, char *delim)
{
    int count = 0;

    while ((str = my_strstr(str, delim))) {
        str += my_strlen(delim);
        count++;
    }
    return (count);
}

char **split_str(char *str, char delim)
{
    char **splited = malloc(sizeof(char *) * (count_char(str, delim) + 2));
    int i;
    int j = 0;

    for (i = 0; str[i]; i++) {
        if (str[i] != delim)
            continue;
        str[i] = '\0';
        if (i > 0) {
            splited[j] = str;
            j++;
        }
        str += i + 1;
        i = -1;
    }
    if (i > 0) {
        splited[j] = str;
        j++;
    }
    splited[j] = NULL;
    return (splited);
}