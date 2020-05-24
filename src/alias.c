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
        if (!strcmp(cmd, tmp->alias)) {
            cmd = strdup(tmp->command);
            tmp = alias;
        }
    }
    return (cmd);
}