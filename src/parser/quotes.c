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

int parse_quotes(char *ptr, char **data)
{
    int length = 0;
    char *ptr_end = strchr(&ptr[1], '\'');

    if (!ptr_end) {
        dprintf(2, "Unmatched '''.\n");
        return (-1);
    }
    length = (ptr_end - ptr) / sizeof(char);
    *data = strndup(&ptr[1], length);
    if (!(*data))
        return (-1);
    (*data)[length - 1] = '\0';
    return (length);
}