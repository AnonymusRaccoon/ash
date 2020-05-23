/*
** EPITECH PROJECT, 2020
** ash
** File description:
** control_commands
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "shell.h"
#include "utility.h"

int eof_command(int key, buffer_t *buffer, env_t *env)
{
    char *ignoreeof = my_getenv(env->vars, "ignoreeof");
    char *eof = my_getenv(env->vars, "eof");
    char new[20];
    unsigned count = eof ? strtol(eof, NULL, 10) : 1;
    unsigned max = 26;

    if (env->window && buffer->buffer && *buffer->buffer)
        return (skip_eof(buffer, env));
    if (!ignoreeof || !env->window)
        return (-1);
    max = get_max_eof(ignoreeof);
    sprintf(new, "%u", ++count);
    env->vars = my_setenv(env->vars, "eof", new);
    if (count >= max)
        return (-1);
    my_addstr(env->window, "\nUse \"exit\" to leave " SHELL_NAME ".\n");
    clearerr(stdin);
    prompt_prepare(buffer, env);
    return (0);
}

bool set_buffer_to_history(buffer_t *buffer, env_t *env)
{
    history_t *hist = env->history;
    char *cmd = NULL;
    int len;

    if (buffer->history_index == 0)
        cmd = buffer->saved_buffer != NULL ? buffer->saved_buffer : "";
    else
        for (int i = 1; i < buffer->history_index && hist; i++)
            hist = hist->next;
    if (!cmd && (!hist || !(cmd = hist->command)))
        return (false);
    if (!buffer->buffer || buffer->size < (len = strlen(cmd))) {
        buffer->buffer = realloc(buffer->buffer, buffer->size + len);
        buffer->size += len;
    }
    if (!buffer->buffer)
        return (false);
    strcpy(buffer->buffer, cmd);
    buffer->pos = strlen(buffer->buffer);
    return (true);
}

int up_history_command(int key, buffer_t *buffer, env_t *env)
{
    if (buffer->buffer && buffer->history_index == 0)
        buffer->saved_buffer = strdup(buffer->buffer);
    buffer->history_index++;
    if (!set_buffer_to_history(buffer, env))
        buffer->history_index--;
    return (0);
}

int down_history_command(int key, buffer_t *buffer, env_t *env)
{
    if (buffer->history_index <= 0)
        return (0);
    buffer->history_index--;
    set_buffer_to_history(buffer, env);
    return (0);
}