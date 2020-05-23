/*
** EPITECH PROJECT, 2020
** ash
** File description:
** builtin_bindkey
*/

#include "shell.h"
#include "key_functions.h"
#include <string.h>
#include <stdio.h>
#include <malloc.h>

int builtin_bindkey(char **argv, env_t *env)
{
    if (!argv[0]) {

    } else if (!strcmp(argv[0], "-l")) {
        for (int i = 0; key_functions[i].name; i++)
            puts(key_functions[i].name);
    }
    free(argv);
    return (0);
}