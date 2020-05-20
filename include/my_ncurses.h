/*
** EPITECH PROJECT, 2020
** ash
** File description:
** my_ncurses
*/

#pragma once


#define KEY_ESCAPE 0x1B
#define ESC(x) ((((int)(x)) << 8u) | KEY_ESCAPE)
#define CSI(x) ((((int)(x)) << 16u) | ESC('['))

#define KEY_UP CSI('A')
#define KEY_DOWN CSI('B')
#define KEY_RIGHT CSI('C')
#define KEY_LEFT CSI('D')
#define KEY_HOME CSI('H')
#define KEY_END CSI('F')
#define KEY_DC CSI(0x7e33)

#include <termios.h>

typedef struct
{
    struct termios old_termios;
    int x;
    int y;
    int w;
    int h;
} my_window;

#define my_refresh() fflush(stdout)
#define NO_MOVE -1

my_window *my_initwin(void);
void my_endwin(my_window *window);

void my_move(my_window *window, int y, int x);
void my_getcuryx(int *y, int *x);
void my_getmaxyx(int *y, int *x);
int my_getch(void);

void my_addstr(my_window *window, const char *str);
#define my_mvaddstr(window, y, x, str) (my_move(window, y, x), \
my_addstr(window, str))


#define COLOR 0
#define BACKGROUND_COLOR 10
#define BRIGHT_MODIFIER 60

#define BLACK 30
#define RED 31
#define GREEN 32
#define YELLOW 33
#define BLUE 34
#define MAGENTA 53
#define CYAN 36
#define WHITE 37

#define my_attron(attr, value) (printf("\x1B[%dm", attr + value))
#define my_attrreset() (printf("\x1B[0m"))


#define my_clrtoeol() (printf("\x1B[K"))
#define my_clrtobot() (printf("\x1B[J"))