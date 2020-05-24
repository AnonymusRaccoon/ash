/*
** EPITECH PROJECT, 2020
** ash
** File description:
** pause_utils
*/

#include "my_ncurses.h"
#include <stddef.h>

void my_npause(my_window *window)
{
    if (!window)
        return;
    tcgetattr(0, &window->saved_termios);
    tcsetattr(0, TCSANOW, &window->old_termios);
}

void my_nresume(my_window *window)
{
    if (!window)
        return;
    tcsetattr(0, TCSANOW, &window->saved_termios);
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