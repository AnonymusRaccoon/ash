/*
** EPITECH PROJECT, 2020
** PSU_minishell1_2019
** File description:
** tcd
*/

#include <criterion/criterion.h>
#include <unistd.h>
#include "shell.h"
#include "builtin.h"

extern char **environ;

Test(cd, home)
{
    env_t *env = malloc(sizeof(env_t));
    env->vars = NULL;
    env->env = malloc(sizeof(char *) * (env_get_length(environ) + 1));
    char **args = malloc(sizeof(char *) * 2);

    args[0] = "cd";
    args[1] = NULL;

    for (int i = 0; environ[i]; i++)
        env->env[i] = strdup(environ[i]);
    builtin_cd(args, env);

    cr_assert_str_eq(getcwd(NULL, 0), my_getenv("HOME"));
}

Test(cd, absolute)
{
    env_t *env = malloc(sizeof(env_t));
    env->vars = NULL;
    env->env = malloc(sizeof(char *) * (env_get_length(environ) + 1));
    char **args = malloc(sizeof(char *) * 3);

    args[0] = "cd";
    args[1] = "/home";
    args[2] = NULL;

    for (int i = 0; environ[i]; i++)
        env->env[i] = strdup(environ[i]);
    builtin_cd(args, env);

    cr_assert_str_eq(getcwd(NULL, 0), "/home");
}

Test(cd, relative)
{
    env_t *env = malloc(sizeof(env_t));
    env->vars = NULL;
    env->env = malloc(sizeof(char *) * (env_get_length(environ) + 1));
    char buf[1024];
    char **args = malloc(sizeof(char *) * 3);

    args[0] = "cd";
    args[1] = "src";
    args[2] = NULL;
    getcwd(buf, 1024);
    strcat(buf, "/src");
    for (int i = 0; environ[i]; i++)
        env->env[i] = strdup(environ[i]);
    builtin_cd(args, env);
    cr_assert_str_eq(getcwd(NULL, 0), buf);
}

Test(cd, minus)
{
    env_t *env = malloc(sizeof(env_t));
    env->vars = NULL;
    env->env = malloc(sizeof(char *) * (env_get_length(environ) + 1));
    char *def = getcwd(NULL, 0);
    char **args1 = malloc(sizeof(char *) * 3);
    char **args2 = malloc(sizeof(char *) * 3);

    args1[0] = "cd";
    args1[1] = "/home";
    args1[2] = NULL;

    args2[0] = "cd";
    args2[1] = "-";
    args2[2] = NULL;

    for (int i = 0; environ[i]; i++)
        env->env[i] = strdup(environ[i]);
    builtin_cd(args1, env);
    builtin_cd(args2, env);

    cr_assert_str_eq(getcwd(NULL, 0), def);
}
