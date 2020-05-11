/*
** EPITECH PROJECT, 2020
** unalias.c
** File description:
** builtin_unalias
*/

#include "shell.h"
#include "builtin.h"
#include <unistd.h>
#include <string.h>

int builtin_unalias(char **argv, env_t *env)
{
    if (!argv[1]) {
        env->vars = my_setenv(env->vars, "?", "1");
        write(2, "unalias: Too few arguments.\n", 28);
        return (0);
    }
    for (int i = 1; argv[i]; i++)
        remove_alias(argv[i], env->alias);
    return (0);
}

void remove_alias(char *alias, alias_t *list)
{
    for (alias_t *tmp = list; tmp; tmp = tmp->next)
        if (tmp->print && strcmp(alias, tmp->alias) == 0)
            tmp->print = 0;
}