/*
** EPITECH PROJECT, 2020
** builtin_echo.c
** File description:
** builtin_echo
*/

#include "builtin.h"
#include <shell.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int builtin_echo(char **argv, env_t *env)
{
    for (int i = 1; argv[i]; i++) {
        print_echo_arg(argv[i], env);
        if (argv[i + 1])
            printf(" ");
    }
    printf("\n");
    fflush(stdout);
    return (0);
}

void print_echo_arg(char *arg, env_t *env)
{
    bool var_interpreter = true;
    bool inhibitor_interpreter = true;

    if (arg[0] == '\'')
        var_interpreter = false;
    if (arg[0] != '\'' && arg[0] != '\"')
        inhibitor_interpreter = false;
    for (int i = 0; arg[i]; i++) {
        if (arg[i] == '\"' || arg[i] == '\'')
            continue;
        if (arg[i] == '$' && arg[i + 1] && var_interpreter) {
            print_var(&arg[i + 1], env);
            for (; arg[i + 1] && arg[i + 1] != ' ' && arg[i + 1] != '\t'; i++);
        } else if (!inhibitor_interpreter && arg[i] < ' ') {
            print_unhibited(arg[i]);
        } else
            printf("%c", arg[i]);
    }
}

void print_var(char *var, env_t *env)
{
    char *isolated_var = strdup(var);
    char *value = NULL;

    for (int i = 0; isolated_var[i]; i++)
        if (isolated_var[i] == ' ' || isolated_var[i] == '\t') {
            isolated_var[i] = 0;
            break;
        }
    if (!(isolated_var[0] >= 'A' && isolated_var[0] <= 'Z')
    && !(isolated_var[0] >= 'a' && isolated_var[0] <= 'z')) {
        printf("Illegal variable name.");
        return;
    }
    value = get_var_value(isolated_var, env);
    if (value)
        printf("%s", value);
    free(isolated_var);
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
    my_setenv(env->vars, "?", "1");
    return (NULL);
}

void print_unhibited(char c)
{
    if (c == '\n')
        c = 'n';
    if (c == '\b')
        c = 'b';
    if (c == '\t')
        c = 't';
    if (c == '\v')
        c = 'v';
    printf("%c", c);
}