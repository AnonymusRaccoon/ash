/*
** EPITECH PROJECT, 2020
** ash
** File description:
** prompt_utilities
*/

#include <stdbool.h>
#include <ctype.h>
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

char *date_format(int date)
{
    static char format[3];

    sprintf(format, "%02d", date);
    return (format);
}

char *str_tolower(char *str)
{
    for (int i = 0; str[i]; i++)
        str[i] = tolower(str[i]);
    return (str);
}