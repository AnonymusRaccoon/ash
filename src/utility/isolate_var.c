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