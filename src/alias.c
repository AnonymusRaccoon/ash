/*
** EPITECH PROJECT, 2020
** alias.c
** File description:
** alias
*/

#include "shell.h"
#include "builtin.h"
#include "utility.h"
#include <unistd.h>
#include <string.h>
#include <stdlib.h>


char *get_alias_command(char *cmd, alias_t *alias)
{
    alias_t *tmp = NULL;

    tmp = alias;
    for (; tmp; tmp = tmp->next) {
        if (!strcmp(cmd, alias->alias)) {
            cmd = strdup(alias->command);
            tmp = alias;
        }
    }
    return (cmd);
}

char *add_separator(char *cmd, int *return_values, int index)
{
    int pos = 0;
    char *new_cmd = NULL;

    if (!cmd)
        return (NULL);
    new_cmd = calloc(strlen(cmd) + 3, sizeof(char));
    if (!new_cmd)
        return (NULL);
    for (int i = 0; cmd[i]; i++)
        new_cmd[i] = cmd[pos++];
    if (return_values[index + 1] != -2) {
        new_cmd[pos] = ';';
        if (return_values[index + 1] == 1) {
            new_cmd[pos++] = '|';
            new_cmd[pos++] = '|';
        } else if (return_values[index + 1] == 0) {
            new_cmd[pos++] = '&';
            new_cmd[pos++] = '&';
        }
    }
    return (new_cmd);
}