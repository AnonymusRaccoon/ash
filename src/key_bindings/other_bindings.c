/*
** EPITECH PROJECT, 2020
** ash
** File description:
** other_bindings
*/

#include "shell.h"
#include "key_functions.h"
#include <stdbool.h>

int quoted_insert_command(int key, buffer_t *buffer, env_t *env)
{
    buffer->quoted_insert = true;
    return (0);
}