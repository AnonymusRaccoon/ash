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
    const char *key;
    const char *func = key_functions[0].name;

    if (binding->key == -1) {
        puts("Unknown key.");
        return;
    }
    key = my_unctrl(binding->key);
    for (int i = 0; key_functions[i].run; i++) {
        if (key_functions[i].run == binding->func) {
            func = key_functions[i].name;
            break;
        }
    }
    printf("%s -> %s\n", key, func);
}

static binding_t *get_binding(const char *c, env_t *env)
{
    int key = my_parsechar(c);

    if (key == -1)
        return (NULL);
    for (int i = 0; env->bindings[i].func; i++)
        if (env->bindings[i].key == key)
            return (&env->bindings[i]);
    return (NULL);
}

static void new_binding(const char *c, int (*func)(int, buffer_t *, env_t *)\
, env_t *env)
{
    int key = my_parsechar(c);
    int size = 0;

    if (env->bindings)
        while (env->bindings[size++].func);
    if (key == -1) {
        printf("Unknown key: %s\n", c);
        return;
    }
    env->bindings = realloc(env->bindings, (size + 1) * sizeof(binding_t));
    env->bindings[size - 1].key = key;
    env->bindings[size - 1].func = func;
    env->bindings[size].func = NULL;
}

static void set_binding(const char *c, const char *cmd, env_t *env)
{
    binding_t *binding = get_binding(c, env);
    int (*func)(int, buffer_t *, env_t *) = NULL;

    for (int i = 0; key_functions[i].run; i++) {
        if (!strcmp(cmd, key_functions[i].name)) {
            func = key_functions[i].run;
            break;
        }
    }
    if (!func) {
        printf("No command found with the name %s\n", cmd);
        return;
    }
    if (binding)
        binding->func = func;
    else
        new_binding(c, func, env);
}

int builtin_bindkey(char **argv, env_t *env)
{
    binding_t *tmp;
    binding_t new_binding = {.key = 0, .func = NULL};

    if (!argv[1]) {
        for (int i = 0; env->bindings && env->bindings[i].func; i++)
            print_binding(&env->bindings[i]);
    } else if (!strcmp(argv[1], "-l")) {
        for (int i = 0; key_functions[i].name; i++)
            puts(key_functions[i].name);
    } else if (!argv[2]) {
        tmp = get_binding(argv[1], env);
        if (!tmp) {
            new_binding.key = my_parsechar(argv[1]);
            tmp = &new_binding;
        }
        print_binding(tmp);
    } else if (!argv[3]) {
        set_binding(argv[1], argv[2], env);
    } else
        puts("Invalid usage of bindkey.");
    return (0);
}