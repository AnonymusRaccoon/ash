/*
** EPITECH PROJECT, 2020
** PSU_minishell1_2019
** File description:
** shell
*/

#include "shell.h"
#include "builtin.h"
#include "key_functions.h"
#include <stdbool.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <errno.h>
#include <ncurses.h>
#include <unistd.h>
#include <termios.h>

int process_key(int key, buffer_t *buffer, env_t *env)
{
    for (int i = 0; env->bindings[i].func; i++)
        if (key == env->bindings[i].key)
            return (env->bindings[i].func(key, buffer, env));
    return (self_insert_command(key, buffer, env));
}

WINDOW *window_create()
{
    // WINDOW *window = initscr();

    // raw();
    // noecho();
    // keypad(window, true);
    // scrollok(window, true);
    // idlok(window, true);
    // return (window);
    struct termios term;

    tcgetattr(0, &term);
    term.c_iflag &= ~(IXON | ICRNL);
    term.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN);
    tcsetattr(0, TCSANOW, &term);
    return (NULL);
}

void window_destroy(WINDOW *window)
{
    if (!window)
        return;
    delwin(window);
    noraw();
    endwin();
}

int buffer_get_display_pos(buffer_t *buffer)
{
    int pos = buffer->startx;
    int tmp;

    for (int i = 0; i < buffer->pos; i++) {
        if (buffer->buffer[i] == '\t') {
            tmp = TABSIZE - pos % TABSIZE;
            pos += tmp == 0 ? TABSIZE : tmp;
        } else
            pos++;
    }
    return pos;
}

void start_shell(env_t *env)
{
    buffer_t buffer = {.size = 0, .buffer = NULL, .pos = 0, .startx = 0};
    int key;
    int y;

    if (isatty(0)) {
        env->window = window_create();
        prompt_prepare(&buffer, env);
    }
    do {

        key = fgetc(stdin);
        printf("%c (%d)\n", key, key);
        printf("Buffer: %s\n", buffer.buffer);
        // if (env->window) {
            // refresh();
            // y = getcury(env->window);
            // mvaddstr(y, buffer.startx, buffer.buffer);
            // clrtoeol();
            // move(y, buffer_get_display_pos(&buffer));
            // key = getch();
        // } else
            // key = fgetc(stdin);
    } while (key != ERR && process_key(key, &buffer, env) >= 0);
    // window_destroy(env->window);
}