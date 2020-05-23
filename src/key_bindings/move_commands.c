/*
** EPITECH PROJECT, 2020
** ash
** File description:
** arrow_commands
*/

#include "shell.h"
#include "key_functions.h"
#include <string.h>

int backward_char_command(int key, buffer_t *buffer, env_t *env)
{
    if (buffer->pos != 0)
        buffer->pos--;
    return (0);
}

int forward_char_command(int key, buffer_t *buffer, env_t *env)
{
    if (buffer->buffer && buffer->buffer[buffer->pos] != '\0')
        buffer->pos++;
    return (0);
}

int beginning_of_line_command(int key, buffer_t *buffer, env_t *env)
{
    buffer->pos = 0;
    return (0);
}

int end_of_line_command(int key, buffer_t *buffer, env_t *env)
{
    buffer->pos = buffer->buffer ? strlen(buffer->buffer) : 0;
    return (0);
}