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
#include <stdlib.h>

int builtin_unalias(char **argv, env_t *env)
{
    if (!argv[1]) {
        env->vars = my_setenv(env->vars, "?", "1");
        write(2, "unalias: Too few arguments.\n", 28);
        return (0);
    }
    for (int i = 1; argv[i]; i++)
        remove_alias(argv[i], &(env->alias));
    return (0);
}

void free_alias(alias_t *alias)
{
    free(alias->alias);
    free(alias->command);
    free(alias);
}

void remove_alias(char *alias, alias_t **list)
{
    alias_t *tmp = *list;

    if (!tmp)
        return;
    if (strcmp(tmp->alias, alias) == 0) {
        *list = tmp->next;
        free_alias(tmp);
        return;
    }
    for (alias_t *ptr = *list; ptr->next; ptr = ptr->next) {
        if (strcmp(ptr->next->alias, alias) == 0) {
            tmp = ptr->next;
            ptr->next = ptr->next->next;
            free_alias(tmp);
            return;
        }
    }
    for (tmp = *list; tmp; tmp = tmp->next->next);
    free_alias(tmp->next);
    tmp->next = NULL;
}