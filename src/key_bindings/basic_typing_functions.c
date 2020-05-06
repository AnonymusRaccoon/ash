/*
** EPITECH PROJECT, 2020
** ash
** File description:
** basic_typing_functions
*/

#include "shell.h"
#include "key_functions.h"
#include <malloc.h>
#include <stddef.h>
#include <ncurses.h>
#include <string.h>

int self_insert_command(int key, buffer_t *buffer, env_t *env)
{
    const char *chars = unctrl(key);
    int charlens = strlen(chars);
    int len = (buffer->buffer ? strlen(buffer->buffer) : 0) + charlens;

    if (len > buffer->size || !buffer->buffer) {
        buffer->buffer = realloc(buffer->buffer, buffer->size + 100);
        buffer->size += 100;
    }
    if (!buffer->buffer)
        return (-1);
    for (int i = len - 1; i >= buffer->pos; i--)
        buffer->buffer[i] = buffer->buffer[i - charlens];
    strcpy(buffer->buffer + buffer->pos, chars);
    buffer->pos++;
    return (0);
}