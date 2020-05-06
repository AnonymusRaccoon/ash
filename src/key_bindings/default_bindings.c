/*
** EPITECH PROJECT, 2020
** ash
** File description:
** default_bindings
*/

#include "shell.h"
#include "key_functions.h"
#include <stddef.h>

const key_function_t key_functions[] = {
    {"self-insert-command", &self_insert_command},
    {NULL, NULL}
};

const binding_t emacs_bindings[] = {
    {0, NULL}
};