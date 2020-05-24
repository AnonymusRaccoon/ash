/*
** EPITECH PROJECT, 2020
** ash
** File description:
** default_bindings
*/

#include "shell.h"
#include "key_functions.h"
#include "my_ncurses.h"
#include <stddef.h>

const key_function_t key_functions[] = {
    {"self-insert-command", &self_insert_command},
    {"newline", &newline_command},
    {"enf-of-file", &eof_command},
    {"backward-delete-char", &backward_delete_char_command},
    {"delete-char", &delete_char_command},
    {"backward-char", &backward_char_command},
    {"forward-char", &forward_char_command},
    {"beginning-of-line", &beginning_of_line_command},
    {"end-of-line", &end_of_line_command},
    {"up-history", &up_history_command},
    {"down-history", &down_history_command},
    {NULL, NULL}
};

const binding_t emacs_bindings[] = {
    {'\n', &newline_command},
    {'\r', &newline_command},
    {CTRL('d'), &eof_command},
    {127, &backward_delete_char_command},
    {KEY_DC, &delete_char_command},
    {KEY_LEFT, &backward_char_command},
    {KEY_RIGHT, &forward_char_command},
    {KEY_HOME, &beginning_of_line_command},
    {KEY_END, &end_of_line_command},
    {KEY_UP, &up_history_command},
    {KEY_DOWN, &down_history_command},
    {'\t', &complete_command},
    {0, NULL}
};