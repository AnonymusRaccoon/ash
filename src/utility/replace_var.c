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
    char *isolated_var = NULL;
    char *value = NULL;
    int var_len = 0;

    if (cmd[0] == '\'')
            return (cmd);
    for (int i = 0; cmd[i]; i++) {
        isolated_var = isolate_var(&cmd[i], env);
        if (!isolated_var)
            return (NULL);
        if (isolated_var == &cmd[i] && cmd[i] != '$')
            continue;
        for (; isolated_var[var_len] && isolated_var[var_len] != ' '
        && isolated_var[var_len] != '\t' &&
        isolated_var[var_len] != '$'; var_len++);
        if (!var_len && cmd[i] != '\"')
            return (cmd);
        value = get_var_value(isolated_var, env);
        if (!value)
            return ("");
        cmd = replace_with_value(cmd, value, var_len);
        i = -1;
    }
    return (cmd);
}

char *isolate_var(char *cmd, env_t *env)
{
    char *isolated_var = NULL;
    char *ptr = NULL;

    for (int i = 0; cmd[i] && !ptr; i++)
        if (cmd[i] == '$')
            ptr = &cmd[i + 1];
    if (!ptr)
        return (cmd);
    if (ptr[0] == 0)
        return (cmd);
    if ((ptr[0] == ' ' || ptr[0] == '\t' ||
        !ptr[0]) && cmd[0] != '\"')
        return (cmd);
    isolated_var = strdup(ptr);
    if (!isolated_var)
        return (NULL);
    for (int i = 0; isolated_var[i]; i++)
        if (isolated_var[i] == ' ' || isolated_var[i] == '\t' || isolated_var[i] == '$')
            isolated_var[i] = 0;
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