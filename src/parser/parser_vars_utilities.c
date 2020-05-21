/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** redirections
*/

#include "parser.h"
#include <stdio.h>
#include <malloc.h>

char *get_var_value(char *var, env_t *env)
{
    char *value;

    if (!var)
        return (NULL);
    value = my_getenv(env->env, var);
    if (value)
        return (value);
    value = my_getenv(env->vars, var);
    if (value)
        return (value);
    printf("%s: Undefined variable.\n", var);
    env->vars = my_setenv(env->vars, "?", "1");
    return (NULL);
}

int get_var_name(char *ptr, char **name)
{
    int length = 0;

    for (int i = 1; ptr[i] && ptr[i] != ' ' && ptr[i] != '$'; i++) {
        length++;
    }
    *name = strndup(&ptr[1], length);
    return (length + 1);
}

void rm_n_char(char *ptr, int n)
{
    int i;

    for (i = 0; ptr[i + n]; i++) {
        ptr[i] = ptr[i + n];
    }
    ptr[i] = '\0';
}

char *process_vars(char *cmd, env_t *env)
{
    char *name = NULL;
    char *value;
    int new_index;
    int length = strlen(cmd);

    for (int i = 0; i < length; i++, length = strlen(cmd)) {
        if (cmd[i] != '$')
            continue;
        new_index = get_var_name(&cmd[i], &name);
        value = get_var_value(name, env);
        if (!value)
            return (NULL);
        cmd = realloc(cmd, sizeof(char) * (strlen(value) + length + 2));
        if (!cmd)
            return (NULL);
        rm_n_char(&cmd[i], strlen(name) + 1);
        insert_substring(cmd, value, i + 1);
        i += new_index;
        free(name);
    }
    return (cmd);
}