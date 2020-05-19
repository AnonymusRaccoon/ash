/*
** EPITECH PROJECT, 2020
** ash
** File description:
** string_utils
*/

#include "my_ncurses.h"
#include <stdio.h>
#include <ncurses.h>

void my_addstr(my_window *window, const char *str)
{
    int tmp;

    for (int i = 0; str[i]; i++) {
        if (str[i] == '\n' || window->x > window->w) {
            window->y++;
            window->x = 0;
        }
        if (str[i] == '\t') {
            tmp = TABSIZE - window->x % TABSIZE;
            window->x += tmp == 0 ? TABSIZE : tmp;
        } else
            window->x++;
    }
    printf("%s", str);
}