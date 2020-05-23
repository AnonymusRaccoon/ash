/*
** EPITECH PROJECT, 2020
** Utility
** File description:
** split_str
*/

#include <string.h>
#include <malloc.h>
#include <stddef.h>

static char *get_delimiter(char *str, char **delims)
{
    for (int i = 0; delims[i]; i++)
        if (!strncmp(str, delims[i], strlen(delims[i])))
            return (delims[i]);
    return (NULL);
}

int count_str(char *str, char *delim)
{
    int count = 0;

    while ((str = strstr(str, delim))) {
        str += strlen(delim);
        count++;
    }
    return (count);
}

static int get_splitted_count(char *str, char **delims)
{
    int count = 1;
    char *delim;

    for (int i = 0; str[i]; i++) {
        delim = get_delimiter(str + i, delims);
        if (delim) {
            count++;
            i += strlen(delim);
        }
    }
    return (count);
}

char **split_str(char *str, char **delims)
{
    char **arr = malloc(sizeof(char *) * (get_splitted_count(str, delims) + 1));
    int index = 0;
    int i;
    char *delim;

    if (!arr)
        return (NULL);
    for (i = 0; str[i]; i++) {
        if (!(delim = get_delimiter(str + i, delims)))
            continue;
        str[i] = '\0';
        arr[index] = str;
        str += i + strlen(delim);
        if (i > 0)
            index++;
        i = -1;
    }
    // if (i > 0)
    arr[index++] = str;
    arr[index] = NULL;
    return (arr);
}