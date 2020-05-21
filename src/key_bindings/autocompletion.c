/*
** EPITECH PROJECT, 2020
** ash
** File description:
** autocompletion
*/

#include "shell.h"

int complete_command(int key, buffer_t *buffer, env_t *env)
{
    if (!buffer->buffer || 
    (!strchr(buffer->buffer, ' ') && !strchr(buffer->buffer, '\t')))
        return (0);
    return (0);
}