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
        printf("%s", argv[i]);
        if (argv[i + 1])
            printf(" ");
    }
    printf("\n");
    fflush(stdout);
    env = (env_t *)(void *)env;
    return (0);
}