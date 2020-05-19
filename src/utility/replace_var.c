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

char * replace_var(char *cmd, env_t *env)
{
    char *isolated_var = NULL;
    char *value = NULL;
    char *new_cmd = NULL;
    int var_len = 0;

    if (cmd[0] == '\'')
        return (cmd);
    isolated_var = isolate_var(cmd, env);
    if (!isolated_var)
        return (NULL);
    if (isolated_var == cmd)
        return (cmd);
    for (; isolated_var[var_len] && isolated_var[var_len] != ' '
    && isolated_var[var_len] != '\t'; var_len++);
    if (!var_len && cmd[0] != '\"')
        return (cmd);
    value = get_var_value(isolated_var, env);
    if (!value)
        return ("");
    new_cmd = replace_with_value(cmd, value, var_len);
    return (new_cmd);
}

char *isolate_var(char *cmd, env_t *env)
{
    char *isolated_var = NULL;

    for (int i = 0; cmd[i] && !isolated_var; i++)
        if (cmd[i] == '$')
            isolated_var = &cmd[i + 1];
    if (!isolated_var)
        return (cmd);
    if (isolated_var[0] == 0)
        return (cmd);
    if ((isolated_var[0] == ' ' || isolated_var[0] == '\t' ||
        !isolated_var[0]) && cmd[0] != '\"')
        return (cmd);
    if (!(isolated_var[0] >= 'A' && isolated_var[0] <= 'Z')
    && !(isolated_var[0] >= 'a' && isolated_var[0] <= 'z')
    && isolated_var[0] != '?') {
        printf("Illegal variable name.\n");
        env->vars = my_setenv(env->vars, "?", "1");
        return (NULL);
    }
    return (isolated_var);
}

char *replace_with_value(char *cmd, char *value, int var_len)
{
    char *new_cmd = calloc(strlen(value) + strlen(cmd), sizeof(char));
    int pos = 0;

    if (!new_cmd)
        return (NULL);
    for (; cmd[pos] && cmd[pos] != '$'; pos++)
        new_cmd[pos] = cmd[pos];
    for (int i = 0; value[i]; i++)
        new_cmd[pos++] = value[i];
    for (int i = 0; i < (var_len + 1 - (int)strlen(value)); i++)
        new_cmd[pos++] = ' ';
    for (; cmd[pos]; pos++)
        new_cmd[pos] = cmd[pos];
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