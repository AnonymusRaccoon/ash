/*
** EPITECH PROJECT, 2020
** ash
** File description:
** basics
*/

#include "my_ncurses.h"
#include <malloc.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>

my_window *my_initwin(void)
{
    my_window *window = calloc(1, sizeof(*window));
    struct termios term;
    struct winsize size;

    if (!window)
        return (NULL);
    tcgetattr(0, &window->old_termios);
    tcgetattr(0, &term);
    term.c_iflag &= ~(IXON | ICRNL);
    term.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN);
    tcsetattr(0, TCSANOW, &term);
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
    window->h = size.ws_row;
    window->w = size.ws_col;
    my_getcuryx(&window->y, &window->x);
    return (window);
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

void my_endwin(my_window *window)
{
    if (!window)
        return;
    tcsetattr(0, TCSANOW, &window->old_termios);
    free(window);
}

void my_move(my_window *window, int y, int x)
{
    if (y == NO_MOVE)
        y = window->y;
    if (x == NO_MOVE)
        x = window->x;
    printf("\x1B[%d;%dH", y + 1, x + 1);
}

int my_getch(void)
{
    char c[4];
    int size = read(1, c, 1);
    int ret = 0;

    if (size < 0)
        return (-1);
    if (size == 1 && c[0] == KEY_ESCAPE)
        size = read(1, &c[1], 3) + 1;
    if (size == 0)
        return (-1);
    for (int i = 0; i < size; i++)
        ret |= c[i] << (8u * i);
    return (ret);
}