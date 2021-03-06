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
    if (key <= 0)
        return (0);
    if (env->window) {
        my_move(env->window, NO_MOVE, env->window->w);
        my_clrtobot();
    }
    if (buffer->quoted_insert) {
        buffer->quoted_insert = false;
        return (self_insert_command(key, buffer, env));
    }
    for (int i = 0; env->bindings[i].func; i++)
        if (key == env->bindings[i].key)
            return (env->bindings[i].func(key, buffer, env));
    return (self_insert_command(key, buffer, env));
}

int buf_getx(buffer_t *buffer, env_t *env)
{
    int pos = buffer->startx;
    int tmp;

    for (int i = 0; i < buffer->pos; i++) {
        if (buffer->buffer[i] == '\t') {
            tmp = TABSIZE - pos % TABSIZE;
            pos += tmp == 0 ? TABSIZE : tmp;
        } else
            pos++;
        if (pos >= env->window->w)
            pos = 0;
    }
    return pos;
}

void shell_refresh(buffer_t *buffer, env_t *env)
{
    static int oldbuffer_pos = 0;
    static int oldwidth = -1;
    if (oldwidth == -1)
        oldwidth = env->window->w;
    if (buffer->buffer && !buffer->buffer[0])
        oldbuffer_pos = 0;
    int y = env->window->y - (oldbuffer_pos + buffer->startx) / oldwidth;
    int newy = y + (buffer->pos + buffer->startx) / env->window->w;

    if (buffer->buffer)
        my_mvaddstr(env->window, y, buffer->startx, buffer->buffer);
    my_clrtoeol();
    my_move(env->window, newy, buf_getx(buffer, env));
    my_refresh();
    oldbuffer_pos = buffer->pos;
    oldwidth = env->window->w;
}

void start_shell(env_t *env)
{
    buffer_t buffer = {NULL, 0, 0, 0, 0, NULL, false};
    int key;

    setup_sigint();
    if (isatty(0)) {
        env->window = my_initwin();
        prompt_prepare(&buffer, env);
    }
    do {
        if (env->window) {
            shell_refresh(&buffer, env);
            key = my_getch();
        } else
            key = fgetc(stdin);
    } while (key != -1 && process_key(key, &buffer, env) >= 0);
    if (buffer.saved_buffer)
        free(buffer.saved_buffer);
    if (buffer.buffer)
        free(buffer.buffer);
    my_endwin(env->window);
}