/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** redirections
*/

#include "parser.h"
#include <stdio.h>

int parse_double_quotes(char *ptr, char **data, env_t *env)
{
    int length = 0;
    char *ptr_end = strchr(&ptr[1], '"');
    char *cmd;

    if (!ptr_end) {
        dprintf(2, "Unmatched '\"'.\n");
        return (-1);
    }
    length = (ptr_end - ptr) / sizeof(char);
    cmd = strndup(&ptr[1], length);
    if (!cmd)
        return (-1);
    cmd[length - 1] = '\0';
    *data = process_vars(cmd, env);
    return (length);
}