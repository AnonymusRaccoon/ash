/*
** EPITECH PROJECT, 2020
** PSU_minishell1_2019
** File description:
** builtin
*/

#include "shell.h"
#include <stdio.h>
#include <string.h>

void remove_duplicate_history(env_t *env)
{
    char *last_command = NULL;
    history_t *tmp = env->history;

    if (!tmp->next)
        return;
    for (;tmp->next; tmp = tmp->next);
    last_command = tmp->command;
    for (tmp = env->history; tmp->next; tmp = tmp->next) {
        if (!strcmp(last_command, tmp->command))
            tmp->print = 0;
        if (!tmp)
            break;
    }
}

int show_history(env_t *env)
{
    for (history_t *tmp = env->history; tmp; tmp = tmp->next) {
        if (tmp->print)
            printf("%6d\t%d:%02d\t%s\n", tmp->index, tmp->hour,
            tmp->minute, tmp->command);
    }
    return (0);
}

int clear_history(env_t *env)
{
    history_t *tmp = NULL;

    for (tmp = env->history; tmp; tmp = tmp->next)
        tmp->print = 0;
    return (0);
}