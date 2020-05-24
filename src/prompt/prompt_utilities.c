/*
** EPITECH PROJECT, 2020
** ash
** File description:
** prompt_utilities
*/

#include <stdbool.h>
#include "my_ncurses.h"

char *minimal_hostname(char *hostname)
{
    int i = 0;

    while (hostname[i] && hostname[i] != '.')
        i++;
    if (hostname[i] == '.')
        hostname[i] = '\0';
    return (hostname);
}

char *prompt_attr(int attr, bool off)
{
    static char str[10];

    sprintf(str, "\x1B[%dm", attr + (off ? DISABLE_ATTR : 0));
    return (str);
}