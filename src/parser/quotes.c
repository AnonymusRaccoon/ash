/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** redirections
*/


#include "shell.h"
#include "redirections.h"
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>
#include "utility.h"
#include "builtin.h"

// takes only the data beetween 2 quotes (for now)
int parse_quotes(char *ptr, char **data)
{
    int length = 0;

    for (; ptr[length]; length++)
        if (ptr[length] == '\'')
            break;
    if (ptr[length] != '\'') {
        dprintf(2, "Unmatched '''.\n");
        return (-1);
    }
    *data = strndup(&ptr[1], length);
    if (!(*data))
        return (-1);
    (*data)[length - 1] = '\0';
    return (length);
}