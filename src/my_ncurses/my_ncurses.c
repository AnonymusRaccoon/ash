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
#include <errno.h>
#include <signal.h>

my_window *stdwin;

void on_resize(int sig, siginfo_t *info, void *context)
{
    my_getmaxyx(&stdwin->h, &stdwin->w);
    my_getcuryx(&stdwin->y, &stdwin->x);
    my_clrtobot();
}

my_window *my_initwin(void)
{
    my_window *window = calloc(1, sizeof(*window));
    struct termios term;
    struct sigaction sa;

    if (!window)
        return (NULL);
    tcgetattr(0, &window->old_termios);
    tcgetattr(0, &term);
    term.c_iflag &= ~(IXON | ICRNL);
    term.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN);
    tcsetattr(0, TCSANOW, &term);
    sa.sa_sigaction = &on_resize;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO;
    sigaction(SIGWINCH, &sa, NULL);
    my_getmaxyx(&window->h, &window->w);
    my_getcuryx(&window->y, &window->x);
    stdwin = window;
    return (window);
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
    window->x = x;
    window->y = y;
    printf("\x1B[%d;%dH", y + 1, x + 1);
}

int my_getch(void)
{
    char c[4];
    int size = read(1, c, 1);
    int ret = 0;

    if (size < 0)
        return (errno == EINTR ? -2 : -1);
    if (size == 1 && c[0] == KEY_ESCAPE)
        size = read(1, &c[1], 3) + 1;
    if (size == 0)
        return (errno == EINTR ? -2 : -1);
    for (int i = 0; i < size; i++)
        ret |= c[i] << (8u * i);
    return (ret);
}