/*
** EPITECH PROJECT, 2020
** ash
** File description:
** clear_utils
*/

#include "my_ncurses.h"
#include <stdio.h>

void my_clrtoeol(void)
{
    printf("\x1B[K");
}