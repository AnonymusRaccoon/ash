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

char *get_alias(char *cmd, alias_t *alias)
{
    char **array = split_commands(cmd);
    int *return_values = get_return_separator(cmd);
    char *final_command = NULL;

    if (!array)
        return (cmd);
    for (int i = 0; array[i]; i++) {
        if (strlen(array[i]) && (strncmp("alias ", array[i], 6)
            && strncmp("unalias ", array[i], 8)))
            array[i] = replace_alias(array[i], alias);
        array[i] = add_separator(array[i], return_values, i);
        if (!array[i])
            return (NULL);
    }
    final_command = fusion(array[0], array);
    return (final_command);
}

char *replace_alias(char *cmd, alias_t *alias)
{
    char **arg_array = split_str(cmd, ' ');
    char *final_str = NULL;

    if (!arg_array)
        return (NULL);
    for (int i = 0; arg_array[i]; i++) {
        arg_array[i] = get_alias_command(arg_array[i], alias);
        if (!arg_array[i])
            return (NULL);
    }
    final_str = fusion(arg_array[0], arg_array);
    return (final_str);
}

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