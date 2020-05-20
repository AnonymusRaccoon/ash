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

/*char **parse_input(char *cmd)
{
    char *data;
    char **ret = malloc(sizeof(char *) * (strlen(cmd) + 1));
    int return_val = 0;
    int inc = 0;
    char *ptr = cmd;
    int inc_for = 1;

    for (int i = 0; cmd[i]; i++, inc_for++) {
        if (cmd[i] >= 33 && cmd[i] <= 126)
            continue;
        if (inc_for == 1) {
            inc_for = 0;
            continue;
        }
        
    }
}*/

bool is_character_valid(char c)
{
    static bool is_valid = false;

    if (is_valid) {
        is_valid = false;
        return (true);
    }
    if (c == '\\') {
        is_valid = true;
    }
    if (c >= 33 && c <= 126)
        return (true);
    return (false);
}

char **parse_input(char *cmd)
{
    int size = strlen(cmd);
    char **ret = malloc(sizeof(char *) * (size + 1));
    char *ptr = cmd;
    int ret_inc = 0;
    char *new;

    for (int i = 0, inc = 1; i <= size; i++, inc++) {
        if (is_character_valid(cmd[i]))
            continue;
        if (inc == 1) {
            ptr = cmd + i + 1;
            inc = 0;
            continue;
        }
        new = strndup(ptr, inc);
        if (!new)
            return (NULL);
        new[strlen(new) - 1] = '\0';
        ret[ret_inc++] = new;
        ptr = cmd + i + 1;
        inc = 0;
    }
    ret[ret_inc] = NULL;
    return (ret);
}