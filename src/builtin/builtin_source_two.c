/*
** EPITECH PROJECT, 2020
** ash
** File description:
** second part of the source function
*/

#include "shell.h"
#include "utility.h"
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

char *get_special_arg_at(char **argv, int len_argv)
{
    char *res = NULL;
    int size = 0;
    int str_index = 0;

    for (int i = 2; argv[i]; i++) {
        size += strlen(argv[i]) + 2;
    }
    size += len_argv - 3;
    res = malloc(sizeof(char) * (size + 1));
    for (int i = 2; i < len_argv; i++) {
        res[str_index++] = '"';
        for (int j = 0; argv[i][j]; j++)
            res[str_index++] = argv[i][j];
        res[str_index++] = '"';
        if (i != len_argv - 1)
            res[str_index++] = ' ';
    }
    res[str_index] = 0;
    return (res);
}

char *get_special_arg_star(char **argv, int len_argv)
{
    char *res = NULL;
    int size = 0;
    int str_index = 0;

    for (int i = 2; argv[i]; i++)
        size += strlen(argv[i]);
    size += len_argv - 3;
    res = malloc(sizeof(char) * (size + 1));
    res[str_index++] = '"';
    for (int i = 2; i < len_argv; i++) {
        for (int j = 0; argv[i][j]; j++)
            res[str_index++] = argv[i][j];
        if (i != len_argv - 1)
            res[str_index++] = ' ';
    }
    res[str_index++] = '"';
    res[str_index] = 0;
    return (res);
}

void init_source_args(char **argv, int len_argv, env_t *env)
{
    char *str = NULL;

    env->vars = my_setenv(env->vars, "*",
                len_argv > 2 ? get_special_arg_at(argv, len_argv) : "");
    env->vars = my_setenv(env->vars, "@",
                len_argv > 2 ? get_special_arg_star(argv, len_argv) : "");
    env->vars = my_setenv(env->vars, "#", tostr(len_argv - 2));
    for (int i = 1; i < len_argv - 1; i++) {
        str = tostr(i);
        env->vars = my_setenv(env->vars, str, strdup(argv[i + 1]));
        free(str);
    }
}

void reset_source_args(int len_argv, env_t *env)
{
    char *str = NULL;

    env->vars = my_unsetenv(env->vars, "#");
    for (int i = 1; i < len_argv - 1; i++) {
        str = tostr(i);
        env->vars = my_unsetenv(env->vars, str);
        free(str);
    }
}