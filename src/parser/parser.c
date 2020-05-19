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
#include <sys/wait.h>
#include <string.h>
#include "utility.h"
#include "parser.h"
#include "builtin.h"

const parser_map parsers[] = {
    {"'", &parse_quotes},
    {NULL, NULL}
};

char **parse_input(char *cmd)
{
    char *data;
    char **ret = malloc(sizeof(char *) * 2);
    int return_val = 0;
    int inc = 0;

    for (int i = 0; cmd[i]; i++) {
        for (int j = 0; parsers[j].key; j++) {
            if (cmd[i] == parsers[j].key)
                return_val = parsers[j].parser(&cmd[i], &data);
            if (return_val == -1)
                return (NULL);
            ret[inc++] = data;
            i += return_val;
        }
    }
}