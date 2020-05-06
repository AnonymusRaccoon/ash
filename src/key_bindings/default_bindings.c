/*
** EPITECH PROJECT, 2020
** ash
** File description:
** default_bindings
*/

#include "shell.h"
#include "key_functions.h"
#include <ncurses.h>
#include <stddef.h>

const key_function_t key_functions[] = {
    {"self-insert-command", &self_insert_command},
    {"newline", &newline_command},
    {"enf-of-file", &eof_command},
    {NULL, NULL}
};

const binding_t emacs_bindings[] = {
    {'\n', &newline_command},
    {CTRL('d'), &eof_command},
    {0, NULL}
};