/*
** EPITECH PROJECT, 2020
** ash
** File description:
** string_utils
*/

#include "my_ncurses.h"
#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>
#include <sys/ioctl.h>

void my_addstr(my_window *window, const char *str)
{
    int tmp;

    for (int i = 0; str[i]; i++) {
        if (str[i] == '\n') {
            window->y++;
            window->x = 0;
        } else if (str[i] == '\t') {
            tmp = TABSIZE - window->x % TABSIZE;
            window->x += tmp == 0 ? TABSIZE : tmp;
        } else
            window->x++;
        if (window->x >= window->w) {
            window->y++;
            window->x = 0;
        }
    }
    printf("%s", str);
}

void my_getmaxyx(int *y, int *x)
{
    struct winsize size;

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
    *y = size.ws_row;
    *x = size.ws_col;
}

void my_getcuryx(int *y, int *x)
{
    my_refresh();
    printf("\x1B[6n");
    fflush(stdout);
    scanf("\x1B[%d;%dR", y, x);
    *y -= 1;
    *x -= 1;
}