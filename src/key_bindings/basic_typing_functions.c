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

    if (len > buffer->size || !buffer->buffer) {
        buffer->buffer = realloc(buffer->buffer, buffer->size + 100);
        buffer->size += 100;
    }
    if (!buffer->buffer)
        return (-1);
    for (int i = len - 1; i >= buffer->pos; i--)
        buffer->buffer[i] = buffer->buffer[i - charslen];
    strcpy(buffer->buffer + buffer->pos, chars);
    buffer->pos += charslen;
    return (0);
}

int newline_command(int key, buffer_t *buffer, env_t *env)
{
    int ret;

    if (!buffer->buffer)
        return (0);
    add_to_history(buffer->buffer, env);
    if (env->window)
        move(getcury(env->window) + 1, 0);
    ret = eval_raw_cmd(buffer->buffer, env);
    buffer->buffer[0] = '\0';
    buffer->pos = 0;
    if (env->window)
        prompt_prepare(buffer, env);
    return (ret);
}