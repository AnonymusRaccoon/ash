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
    env->vars = my_setenv(env->vars, "?", "1");
    return (0);
}

int add_to_history(char *cmd, env_t *env)
{
    time_t time_struct;
    struct tm *curr_time = 0;
    history_t *log = malloc(sizeof(history_t));
    history_t *tmp = env->history;
    char *command = cmd;

    for (; *command && (*command == ' ' || *command == '\t'); command++);
    if (!strlen(command)) {
        free(log);
        return (0);
    }
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

int list_len(history_t *list)
{
    int len = 0;
    history_t *tmp = NULL;

    for (tmp = list; tmp; tmp = tmp->next)
        len++;
    return (len);
}

int execute_from_history(char **args, env_t *env)
{
    int len = list_len(env->history);
    history_t *tmp = NULL;
    history_t *last = NULL;

    for (tmp = env->history; tmp; tmp = tmp->next)
        if (!tmp->next)
            last = tmp;
    for (int i = 0; i < len; i++) {
        tmp = env->history;
        for (int m = 0; m < len - i - 1; m++)
            tmp = tmp->next;
        if (tmp->print && strncmp(&args[0][1], tmp->command,
            strlen(args[0]) - 1) == 0)
            return (execute_command_history(tmp, last, args, env));
    }
    printf("%s: Event not found.\n", &args[0][1]);
    env->vars = my_setenv(env->vars, "?", "1");
    return (0);
}

int execute_command_history(history_t *old, history_t *new,
char **args, env_t *env)
{
    old->print = 0;
    new->command = fusion(old->command, args);
    if (!new->command)
        return (-1);
    printf("%s\n", new->command);
    return (eval_raw_cmd(new->command, env));
}