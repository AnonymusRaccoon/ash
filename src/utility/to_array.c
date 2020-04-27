/*
** EPITECH PROJECT, 2020
** PSU_minishell1_2019
** File description:
** to_array
*/

#include <stddef.h>
#include <malloc.h>
#include <string.h>

static int get_word_count(char *str)
{
    int count = 0;

    if (!str)
        return (0);
    for (int i = 0; str[i]; i++) {
        if (str[i] == ':')
            count++;
    }
    return (count);
}

char **to_array(char *str)
{
    int count = get_word_count(str);
    char **arr;
    char *p = str;
    int i = 1;

    if (!str)
        return (NULL);
    arr = malloc(sizeof(char *) * (count + 2));
    if (!arr)
        return (NULL);
    arr[0] = str;
    for (i = 1; (p = strchr(p, ':')); i++) {
        *p = '\0';
        p++;
        arr[i] = p;
    }
    arr[i] = NULL;
    return (arr);
}