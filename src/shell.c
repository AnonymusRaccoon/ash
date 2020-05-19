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
#include <unistd.h>
#include <sys/select.h>
#include <termios.h>
#include <ncurses.h>
#include "my_ncurses.h"

int process_key(int key, buffer_t *buffer, env_t *env)
{
    for (int i = 0; env->bindings[i].func; i++)
        if (key == env->bindings[i].key)
            return (env->bindings[i].func(key, buffer, env));
    return (self_insert_command(key, buffer, env));
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

    if (isatty(0)) {
        env->window = my_initwin();
        prompt_prepare(&buffer, env);
    }
    do {
        if (env->window) {
            if (buffer.buffer)
                my_mvaddstr(env->window, NO_MOVE, buffer.startx, buffer.buffer);
            my_clrtoeol();
            my_move(env->window, NO_MOVE, buffer_get_display_pos(&buffer));
            my_refresh();
            key = my_getch();
        } else
            key = fgetc(stdin);
    } while (key != -1 && process_key(key, &buffer, env) >= 0);
    my_endwin(env->window);
}