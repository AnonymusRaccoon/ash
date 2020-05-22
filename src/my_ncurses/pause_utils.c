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