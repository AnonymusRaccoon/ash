/*
** EPITECH PROJECT, 2020
** ash
** File description:
** control_commands
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"
#include "utility.h"

int get_max_eof(char *ignoreeof)
{
    bool correct = true;

    for (int i = 0; ignoreeof[i] && correct; i++)
        if(!is_num(ignoreeof[i]))
            correct = false;
    if (correct && strcmp(ignoreeof, "0") && strcmp(ignoreeof, ""))
        return(strtol(ignoreeof, NULL, 10));
    return (26);
}

int skip_eof(buffer_t *buffer, env_t *env)
{
    my_addstr(env->window, "\n");
    prompt_prepare(buffer, env);
    return (0);
}

int eof_command(int key, buffer_t *buffer, env_t *env)
{
    static unsigned count = 0;
    unsigned max = 26;
    char *ignoreeof = my_getenv(env->vars, "ignoreeof");

    if (env->window && buffer->buffer && *buffer->buffer)
        return (skip_eof(buffer, env));
    if (!ignoreeof || !env->window)
        return (-1);
    max = get_max_eof(ignoreeof);
    count++;
    if (count >= max)
        return (-1);
    my_addstr(env->window, "\n");
    clearerr(stdin);
    fprintf(stdout, "Use \"exit\" to leave %s.\n", SHELL_NAME);
    prompt_prepare(buffer, env);
    return (0);
}