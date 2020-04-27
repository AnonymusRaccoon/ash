/*
** EPITECH PROJECT, 2019
** task1 day13
** File description:
** none
*/

#include <stddef.h>

char *my_strchr(char *str, char c)
{
    for (int i = 0; str[i]; i++)
        if (str[i] == c)
            return (str + i);
    return (NULL);
}