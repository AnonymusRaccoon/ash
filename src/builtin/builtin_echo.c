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
        for (int j = 0; argv[i][j]; j++)
            j += print_char(argv[i], j);
        if (argv[i + 1])
            printf(" ");
    }
    printf("\n");
    fflush(stdout);
    env->vars = my_setenv(env->vars, "?", "0");
    return (0);
}

int print_char(char *str, int i)
{
    if (str[i] == '\\' && str[i + 1] == 'a')
        return (printf("\a"));
    if (str[i] == '\\' && str[i + 1] == 'b')
        return (printf("\b"));
    if (str[i] == '\\' && str[i + 1] == 't')
        return (printf("\t"));
    if (str[i] == '\\' && str[i + 1] == 'n')
        return (printf("\n"));
    if (str[i] == '\\' && str[i + 1] == 'v')
        return (printf("\v"));
    if (str[i] == '\\' && str[i + 1] == 'f')
        return (printf("\f"));
    if (str[i] == '\\' && str[i + 1] == 'r')
        return (printf("\r"));
    if (str[i] == '\\') {
        printf("\\%c", str[i + 1]);
        return (1);
    }
    printf("%c", str[i]);
    return (0);
}