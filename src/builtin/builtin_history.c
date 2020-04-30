/*
** EPITECH PROJECT, 2020
** PSU_minishell1_2019
** File description:
** builtin
*/

#include "shell.h"
#include "builtin.h"
#include "redirections.h"
#include "time.h"
#include "utility.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int builtin_history(char **args, env_t *env)
{
    if (**args == '!')
        return (execute_from_history(args, env));
    if (!args[1])
        return (show_history(env));
    if (args[1]) {
        if (!strcmp(args[1], "-c"))
            return (clear_history(env));
    }
    return (1);
}

int add_to_history(char *cmd, env_t *env)
{
    time_t time_struct;
    struct tm *curr_time = 0;
    history_t *log = malloc(sizeof(history_t));
    history_t *tmp = env->history;
    char *command = cmd;

    for (; *command && (*command == ' ' || *command == '\t'); command++);
    if (!strlen(command))
        return (0);
    if (!log)
        return (-1);
    for (tmp = env->history; tmp && tmp->next; tmp = tmp->next);
    time(&time_struct);
    curr_time = localtime(&time_struct);
    *log = (history_t){tmp ? tmp->index + 1 : 1, strdup(command),
        curr_time->tm_hour, curr_time->tm_min, 1, NULL};
    (env->history) ? (tmp->next = log) : (env->history = log);
    remove_duplicate_history(env);
    return (0);
}

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

int execute_from_history(char **args, env_t *env)
{
    int len = 0;
    history_t *tmp = NULL;
    history_t *last = NULL;

    for (tmp = env->history; tmp; tmp = tmp->next) {
        if (!tmp->next)
            last = tmp;
        len++;
    }
    for (int i = 0; i < len; i++) {
        tmp = env->history;
        for (int m = 0; m < len - i - 1; m++)
            tmp = tmp->next;
        if (!tmp->print)
            continue;
        if (strncmp(&args[0][1], tmp->command, strlen(args[0]) - 1) == 0) {
            tmp->print = 0;
            last->command = strdup(fusion(tmp->command, args));
            printf("%s\n", last->command);
            return (eval_raw_cmd(last->command, env));
        }
    }
    printf("%s: Event not found.\n", &args[0][1]);
    my_setenv(env->env, "?", "1");
    return (0);
}