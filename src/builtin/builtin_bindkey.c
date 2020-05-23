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
#include "my_ncurses.h"

void print_binding(binding_t *binding)
{
    const char *key = my_unctrl(binding->key);
    const char *func = NULL;

    for (int i = 0; key_functions[i].run; i++) {
        if (key_functions[i].run == binding->func) {
            func = key_functions[i].name;
            break;
        }
    }
    printf("%s -> %s\n", key, func);
}

int builtin_bindkey(char **argv, env_t *env)
{
    binding_t *tmp;

    if (!argv[1]) {
        if (!env->bindings)
            return (0);
        for (int i = 0; env->bindings[i].func; i++)
            print_binding(&env->bindings[i]);
    } else if (!strcmp(argv[1], "-l")) {
        for (int i = 0; key_functions[i].name; i++)
            puts(key_functions[i].name);
    } else if (!argv[2]) {
        // for (tmp = env->bindings; tmp && tmp->key != )
        print_binding(tmp);
    } else if (!argv[3]) {

    } else
        puts("Invalid usage of bindkey.");
    free(argv);
    return (0);
}