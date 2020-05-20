/*
** EPITECH PROJECT, 2020
** ash
** File description:
** basic_typing_functions
*/

#include "shell.h"
#include "builtin.h"
#include "key_functions.h"
#include "utility.h"
#include <termios.h>
#include <malloc.h>
#include <stddef.h>
#include <ncurses.h>
#include <string.h>

int self_insert_command(int key, buffer_t *buffer, env_t *env)
{
    const char *chars = key == '\t' ? "\t" : unctrl(key);
    int charslen = strlen(chars);
    int len = (buffer->buffer ? strlen(buffer->buffer) : 0) + charslen;

    if (len >= buffer->size || !buffer->buffer) {
        buffer->buffer = realloc(buffer->buffer, buffer->size + 100);
        buffer->size += 100;
    }
    if (!buffer->buffer)
        return (-1);
    for (int i = len - 1; i > buffer->pos; i--)
        buffer->buffer[i] = buffer->buffer[i - charslen];
    memcpy(buffer->buffer + buffer->pos, chars, charslen);
    buffer->buffer[len] = '\0';
    buffer->pos += charslen;
    return (0);
}

int backward_delete_char_command(int key, buffer_t *buffer, env_t *env)
{
    int len = buffer->buffer ? strlen(buffer->buffer) : 0;

    if (buffer->pos == 0)
        return (0);
    buffer->pos--;
    for (int i = buffer->pos; i < len; i++)
        buffer->buffer[i] = buffer->buffer[i + 1];
    return (0);
}

int delete_char_command(int key, buffer_t *buffer, env_t *env)
{
    int len = buffer->buffer ? strlen(buffer->buffer) : 0;

    for (int i = buffer->pos; i < len; i++)
        buffer->buffer[i] = buffer->buffer[i + 1];
    return (0);
}

int newline_command(int key, buffer_t *buffer, env_t *env)
{
    int ret;

    if (env->window)
        my_addstr(env->window, "\n");
    if (buffer->buffer) {
        add_to_history(buffer->buffer, env);
        ret = eval_raw_cmd(buffer->buffer, env);
        buffer->buffer[0] = '\0';
        buffer->pos = 0;
        my_getcuryx(&env->window->y, &env->window->x);
    }
    if (env->window && ret >= 0)
        prompt_prepare(buffer, env);
    return (ret);
}