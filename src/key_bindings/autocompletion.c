/*
** EPITECH PROJECT, 2020
** ash
** File description:
** autocompletion
*/

#define _GNU_SOURCE
#include "shell.h"
#include "utility.h"
#include <glob.h>
#include <malloc.h>
#include <stdio.h>
#include <string.h>

char *get_start_of_current_arg(buffer_t *buffer)
{
    if (!buffer->buffer)
        return (NULL);
    return (memrchr(buffer->buffer, ' ', buffer->pos) + 1);
}

void print_results(unsigned count, char **results)
{
    unsigned size = 0;

    putchar('\n');
    my_clrtobot();
    for (unsigned i = 0; i < count; i++)
        size = MAX(size, strlen(results[i]));
    size++;
    for (unsigned i = 0; i < count; i++)
        printf("%-*s", size, results[i]);
}

void buffer_replace(buffer_t *buffer, char *to_replace, int start, int end)
{
    int len = strlen(to_replace);
    int total = len + (buffer->buffer ? strlen(buffer->buffer) : 0);

    if (buffer->size < total) {
        buffer->buffer = realloc(buffer->buffer, total  + 50);
        buffer->size = total + 50;
    }
    if (!buffer->buffer)
        return;
    for (int i = strlen(buffer->buffer); i >= end; i--)
        buffer->buffer[i + len - 1] = buffer->buffer[i];
    memcpy(buffer->buffer + start, to_replace, len);
    buffer->buffer[total - (end - start)] = '\0';
}

void complete_current(buffer_t *buffer, char *cmd)
{
    char *start = get_start_of_current_arg(buffer);
    char *end;

    if (!start)
        return;
    end = strchr(start, ' ');
    if (!end)
        end = buffer->buffer + strlen(buffer->buffer);
    buffer_replace(buffer, cmd, start - buffer->buffer, end - buffer->buffer);
    buffer->pos = start - buffer->buffer + strlen(cmd);
}

int complete_command(int key, buffer_t *buffer, env_t *env)
{
    char *str;
    char *p = get_start_of_current_arg(buffer);
    glob_t result;

    if (!buffer->buffer || !p)
        return (0);
    str = malloc(buffer->pos - (p - buffer->buffer) + 2);
    strncpy(str, p, buffer->pos - (p - buffer->buffer));
    str[buffer->pos - (p - buffer->buffer)] = '\0';
    strcat(str, "*");
    if (!glob(str, GLOB_MARK | GLOB_BRACE, NULL, &result)) {
        if (result.gl_pathc == 1)
            complete_current(buffer, result.gl_pathv[0]);
        else
            print_results(result.gl_pathc, result.gl_pathv);
    }
    globfree(&result);
    free(str);
    return (0);
}