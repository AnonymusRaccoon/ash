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

int builtin_env(char **argv, env_t *env)
{
    for (int i = 0; env->env[i]; i++) {
        write(1, env->env[i], strlen(env->env[i]));
        write(1, "\n", 1);
    }
    free(argv);
    return (0);
}

int builtin_setenv(char **argv, env_t *env)
{
    if (!argv[1])
        return (builtin_env(argv, env));
    if ((!('a' <= argv[1][0] && argv[1][0] <= 'z'))
    && (!('A' <= argv[1][0] && argv[1][0] <= 'Z'))) {
        write(2, "setenv: Variable name must begin with a letter.\n", 49);
        env->vars = my_setenv(env->vars, "?", "1");
        return (0);
    }
    if (!envvar_is_valid(argv[1])) {
        write(2, INVALID_ENV_VAR, strlen(INVALID_ENV_VAR));
        env->vars = my_setenv(env->vars, "?", "1");
        return (0);
    }
    env->env = my_setenv(env->env, argv[1], argv[2]);
    free(argv);
    return (0);
}

int builtin_unsetenv(char **argv, env_t *env)
{
    if (!argv[1]) {
        write(2, "unsetenv: Too few arguments.\n", 29);
        env->vars = my_setenv(env->vars, "?", "1");
        free(argv);
        return (0);
    }
    for (int i = 1; argv[i]; i++)
        if (!strchr(argv[i], '='))
            env->env = my_unsetenv(env->env, argv[i]);
    free(argv);
    return (0);
}