/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** redirections
*/

#define _XOPEN_SOURCE

#include "parser.h"
#include "shell.h"
#include "redirections.h"
#include "utility.h"
#include "builtin.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>

char *strdup(const char *);

int count_trailing_spaces(char *cmd)
{
    int i = 0;

    for (i = 0; cmd[i]; i++)
        if (cmd[i] != ' ' && cmd[i] != '\t')
            break;
    return (i);
}

char **parse_input(char *cmd, env_t *env, wordexp_t *parser)
{
    int bin_len;

    cmd = strdup(cmd + count_trailing_spaces(cmd));
    for (bin_len = 0; cmd[bin_len]; bin_len++) {
        if (cmd[bin_len] == ' ' || cmd[bin_len] == '\t')
            break;
    }
    cmd = process_vars(cmd, env);
    for (alias_t *al = env->alias; al; al = al->next) {
        if (!strncmp(al->alias, cmd, bin_len)) {
            cmd = realloc(cmd, strlen(cmd) + strlen(al->command) + 1 - bin_len);
            rm_n_char(cmd, bin_len);
            insert_substring(cmd, al->command, 1);
        }
    }
    if (wordexp(cmd, parser, WRDE_SHOWERR)) {
        perror(SHELL_NAME);
        return (NULL);
    }
    free(cmd);
    return (parser->we_wordv);
}