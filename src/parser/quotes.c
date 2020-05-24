/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** redirections
*/

#include "parser.h"
#include <stdio.h>

int parse_quotes(char *ptr, char **data, env_t *env)
{
    int length = 0;
    char *ptr_end = strchr(&ptr[1], '\'');
    (void)env;

    if (!ptr_end) {
        dprintf(2, "Unmatched '''.\n");
        return (-1);
    }
    length = (ptr_end - ptr) / sizeof(char);
    *data = strndup(&ptr[1], length);
    if (!(*data))
        return (-1);
    (*data)[length - 1] = '\0';
    return (length);
}