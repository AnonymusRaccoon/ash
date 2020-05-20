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

char *clean_var(char *var)
{
    for (int i = 0; var[i]; i++)
        if (var[i] == ' ' || var[i] == '\t'
            || var[i] == '$')
            var[i] = 0;
    return (var);
}

bool var_name_is_correct(char *var, env_t *env)
{
    if (!(var[0] >= 'A' && var[0] <= 'Z')
    && !(var[0] >= 'a' && var[0] <= 'z')
    && var[0] != '?') {
        printf("Illegal variable name.\n");
        env->vars = my_setenv(env->vars, "?", "1");
        return (false);
    }
    return (true);
}

char *isolate_var(char *cmd, env_t *env)
{
    char *var = NULL;
    char *ptr = NULL;

    for (int i = 0; cmd[i] && !ptr; i++)
        if (cmd[i] == '$')
            ptr = &cmd[i + 1];
    if (!ptr)
        return (cmd);
    if (!ptr[0])
        return (cmd);
    if ((ptr[0] == ' ' || ptr[0] == '\t' ||
        !ptr[0]) && cmd[0] != '\"')
        return (cmd);
    var = strdup(ptr);
    if (!var)
        return (NULL);
    var = clean_var(var);
    if (!var_name_is_correct(var, env))
        return (NULL);
    return (var);
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