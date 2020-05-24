/*
** EPITECH PROJECT, 2020
** ash
** File description:
** string_utils
*/

#include "my_ncurses.h"
#include <stdio.h>
#include <unctrl.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>

int get_escape_character_length(const char *str)
{
    int i = 0;

    if (str[1] != '[')
        return (1);
    while (str[i] && str[i] != 'm')
        i++;
    return (i);
}

void my_addstr(my_window *window, const char *str)
{
    int tmp;

    for (int i = 0; str[i]; i++) {
        if (str[i] == KEY_ESCAPE) {
            i += get_escape_character_length(&str[i]);
            continue;
        }
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

const char *my_unctrl(int c)
{
    static char str[5];

    if (c == KEY_DC)
        return "^?";
    if ((c & 0xFFFF) == CSI(0)) {
        str[0] = '^';
        str[1] = '[';
        str[2] = c >> 16u;
        str[3] = c >> 24u;
        str[4] = '\0';
        return (str);
    }
    return (unctrl(c));
}

int my_parsechar(const char *c)
{
    if (!strcmp(c, "^?"))
        return (KEY_DC);
    if (c[0] == '^' && c[1] == '[')
        return (CSI(c[2] | c[3] << 8u));
    if (c[1])
        return (-1);
    return (c[0]);
}