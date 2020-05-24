/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** builtin_env
*/

#include <unistd.h>
#include "shell.h"
#include <malloc.h>
#include <errno.h>
#include <string.h>

int builtin_set(char **argv, env_t *env)
{
    if (!argv[1]) {
        for (int i = 0; env->vars && env->vars[i]; i++)
            puts(env->vars[i]);
        env->vars = my_setenv(env->vars, "?", "0");
        return (0);
    }
    if ((!('a' <= argv[1][0] && argv[1][0] <= 'z'))
    && (!('A' <= argv[1][0] && argv[1][0] <= 'Z'))) {
        dprintf(2, "set: Variable name must begin with a letter.\n");
        env->vars = my_setenv(env->vars, "?", "1");
        return (0);
    }
    if (!envvar_is_valid(argv[1])) {
        dprintf(2, INVALID_VAR);
        env->vars = my_setenv(env->vars, "?", "1");
        return (0);
    }
    env->vars = my_setenv(env->vars, argv[1], argv[2]);
    env->vars = my_setenv(env->vars, "?", "0");
    return (0);
}

int builtin_unset(char **argv, env_t *env)
{
    if (!argv[1]) {
        dprintf(2, "unset: Too few arguments.\n");
        env->vars = my_setenv(env->vars, "?", "1");
        return (0);
    }
    for (int i = 1; argv[i]; i++)
        if (!strchr(argv[i], '='))
            env->vars = my_unsetenv(env->vars, argv[i]);
    env->vars = my_setenv(env->vars, "?", "0");
    return (0);
}