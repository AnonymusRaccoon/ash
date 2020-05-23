/*
** EPITECH PROJECT, 2020
** buitlin_alias.c
** File description:
** builtin_alias
*/

#include "shell.h"
#include "builtin.h"
#include <utility.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int builtin_alias(char **argv, env_t *env)
{
    if (!argv[1]) {
        print_aliases(env->alias);
        env->vars = my_setenv(env->vars, "?", "0");
    } else if (argv[1]) {
        env->vars = my_setenv(env->vars, "?", "0");
        return (add_alias(&(env->alias), argv[1], &argv[2]));
    }
    return (0);
}

int add_alias(alias_t **list, char *alias, char **command)
{
    alias_t *elem = NULL;

    if (!command[0])
        return (0);
    elem = malloc(sizeof(alias_t));
    if (!elem)
        return (-1);
    elem->alias = strdup(alias);
    elem->command = concatenate(command);
    elem->next = NULL;
    if (!elem->command || !elem->alias)
        return (-1);
    if (*list == NULL) {
        *list = elem;
        return (0);
    }
    return (add_alias_to_list(list, elem, alias));
}

int add_alias_to_list(alias_t **list, alias_t *elem, char *alias)
{
    alias_t *tmp = *list;

    for (tmp = *list; tmp; tmp = tmp->next) {
        if (!strcmp(alias, tmp->alias)) {
            tmp->command = elem->command;
            free(elem);
            return (0);
        }
        if (tmp == *list && strcmp(tmp->alias, alias) > 0) {
            elem->next = tmp;
            *list = elem;
            return (0);
        } else if (tmp->next && strcmp(tmp->next->alias, alias) > 0) {
            elem->next = tmp->next;
            tmp->next = elem;
            return (0);
        }
    }
    for (tmp = *list; tmp->next; tmp = tmp->next);
    tmp->next = elem;
    return (0);
}

char *concatenate(char **command)
{
    char *concatened = NULL;
    int total_len = 2;
    int pos = 0;

    if (!command[1])
        return (strdup(command[0]));
    for (int i = 0; command[i]; i++)
        total_len += strlen(command[i]) + 1;
    concatened = calloc(total_len + 1, sizeof(char));
    if (!concatened)
        return (NULL);
    if (command[1])
        concatened[pos++] = '(';
    for (int i = 0; command[i]; i++) {
        for (int k = 0; command[i][k]; k++)
            concatened[pos++] = command[i][k];
        concatened[pos++] = command[i + 1] ? ' ' : ')';
    }
    return (concatened);
}

void print_aliases(alias_t *list)
{
    for (alias_t *tmp = list; tmp; tmp = tmp->next)
        printf("%s\t%s\n", tmp->alias, tmp->command);
}