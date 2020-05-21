/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** redirections
*/


#include "shell.h"
#include "redirections.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "utility.h"
#include "parser.h"
#include "builtin.h"
#include <malloc.h>

const parser_map parsers[] = {
    {'\'', &parse_quotes},
    {'"', &parse_double_quotes},
    {'\0', NULL}
};

bool is_character_valid(char c)
{
    static bool is_valid = false;

    if (is_valid) {
        is_valid = false;
        return (true);
    }
    if (c == '\\') {
        is_valid = true;
    }
    return (c >= 33 && c <= 126);
}

int call_parsers(char *cmd, int index, char **data, env_t *env)
{
    int new_index = 0;

    for (int i = 0; parsers[i].key; i++) {
        if (cmd[index] != parsers[i].key)
            continue;
        new_index = parsers[i].parser(&cmd[index], data, env);
        if (!(*data))
            return (-1);
        return (new_index);
    }
    return (0);
}

int manage_specials_parsers(char *cmd, char **buffer, int *inc, env_t *env)
{
    int new_index = 0;
    char *data = NULL;

    new_index = call_parsers(cmd, 0, &data, env);
    if (new_index == -1)
        return (-1);
    if (new_index > 0) {
        (*inc)--;
        *buffer = add_to_buffer(*buffer, &cmd[(*inc) * -1], (*inc), env);
        *buffer = add_to_buffer(*buffer, data, strlen(data), NULL);
        free(data);
        (*inc) = 0;
        if (!(*buffer))
            return (-1);
        return (new_index);
    }
    return (0);
}

int parser_loop(char *cmd, char **buffer, char **ptr, void **pack)
{
    int *i = pack[0];
    int *inc = pack[1];
    int *new_index = pack[2];
    env_t *env = pack[3];

    if (is_character_valid(cmd[*i])) {
        (*new_index) = manage_specials_parsers(&cmd[(*i)], buffer, inc, env);
        if ((*new_index) == -1)
            return (-1);
        (*i) += (*new_index);
        if (*new_index)
            (*ptr) = cmd + (*i) + 1;
        return (1);
    }
    if (*inc == 1 && !(*new_index)) {
        (*ptr) = cmd + (*i) + 1;
        (*inc) = 0;
        return (1);
    }
    return (0);
}

char **parse_input(char *cmd, env_t *env)
{
    char **ret = malloc(sizeof(char *) * (strlen(cmd) + 1));
    char *ptr = cmd;
    int idx[3] = {0};
    char *buf = NULL;

    if (!ret)
        return (NULL);
    for (int i = 0, inc = 1; i <= (int)strlen(cmd); i++, inc++) {
        idx[2] = parser_loop(cmd, &buf, &ptr, (void *[4]){&i, &inc, &idx[1], env});
        if (idx[2] < 0)
            return (NULL);
        else if (idx[2])
            continue;
        if (!(buf = add_to_buffer(buf, ptr, inc - 1, env)))
            return (NULL);
        ret[idx[0]++] = buf;
        ptr = cmd + i + 1;
        buf = idx[1] = inc = 0;
    }
    ret[idx[0]] = NULL;
    return (ret);
}