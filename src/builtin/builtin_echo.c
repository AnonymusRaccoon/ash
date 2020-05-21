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
        for (int j = 0; argv[i][j]; j++) {
            if (argv[i][j] == '\\')
                j++;
            printf("%c", argv[i][j]);
        }
        if (argv[i + 1])
            printf(" ");
    }
    printf("\n");
    fflush(stdout);
    env->vars = my_setenv(env->vars, "?", "0");
    return (0);
}