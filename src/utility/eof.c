/*
** EPITECH PROJECT, 2020
** ash
** File description:
** eof
*/

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
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