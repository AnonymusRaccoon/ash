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

void init_source_args(char **argv, int len_argv, env_t *env)
{
    char *str = NULL;

    for (int i = 1; i < len_argv - 1; i++) {
        str = tostr(i);
        env->vars = my_setenv(env->vars, str, strdup(argv[i + 1]));
        free(str);
    }
}

void reset_source_args(int len_argv, env_t *env)
{
    char *str = NULL;

    for (int i = 1; i < len_argv - 1; i++) {
        str = tostr(i);
        env->vars = my_unsetenv(env->vars, str);
        free(str);
    }
}