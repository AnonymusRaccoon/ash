/*
** EPITECH PROJECT, 2020
** get_var.c
** File description:
** get_var
*/

#include <shell.h>
#include <stdlib.h>
#include <stdio.h>
#include "utility.h"
#include "shell.h"
#include <string.h>

char *replace_var(char *cmd, env_t *env)
{
    char *var = NULL;
    char *value = NULL;
    int var_len = 0;

    for (int i = 0; cmd[i]; i++) {
        var = isolate_var(&cmd[i], env);
        if (!var)
            return (NULL);
        if (var == &cmd[i] && cmd[i] != '$')
            continue;
        for (; var[var_len] && var[var_len] != ' ' && var[var_len] != '\t'
        && var[var_len] != '$'; var_len++);
        if (!var_len && cmd[i] != '\"')
            return (cmd);
        value = get_var_value(var, env);
        if (!value)
            return (NULL);
        cmd = replace_with_value(cmd, value, var_len);
        i = -1;
    }
    return (cmd);
}

char *replace_with_value(char *cmd, char *value, int var_len)
{
    char *new_cmd = calloc(strlen(value) + strlen(cmd), sizeof(char));
    int pos = 0;
    int pos_cmd = 0;

    if (!new_cmd)
        return (NULL);
    for (; cmd[pos_cmd] && cmd[pos_cmd] != '$'; pos_cmd++)
        new_cmd[pos++] = cmd[pos_cmd];
    for (int i = 0; value[i]; i++)
        new_cmd[pos++] = value[i];
    pos_cmd += var_len + 1;
    for (; cmd[pos_cmd]; pos_cmd++)
        new_cmd[pos++] = cmd[pos_cmd];
    while (new_cmd[strlen(new_cmd) - 1] == ' ')
        new_cmd[strlen(new_cmd) - 1] = 0;
    return (new_cmd);
}

char *get_var_value(char *var, env_t *env)
{
    char *value = my_getenv(env->env, var);

    if (value)
        return (value);
    value = my_getenv(env->vars, var);
    if (value)
        return (value);
    printf("%s: Undefined variable.\n", var);
    env->vars = my_setenv(env->vars, "?", "1");
    return (NULL);
}