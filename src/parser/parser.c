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
int dprintf(int, const char *, ...);

int count_trailing_spaces(char *cmd)
{
    int i = 0;

    for (i = 0; cmd[i]; i++)
        if (cmd[i] != ' ' && cmd[i] != '\t')
            break;
    return (i);
}

char **remove_leading_entries(char **cmds)
{
    if (!cmds)
        return (NULL);
    for (int i = 0; cmds[i]; i++)
        if (cmds[i][count_trailing_spaces(cmds[i])])
            return (cmds + i);
    return (cmds);
}

char *process_aliases(char *cmd, env_t *env)
{
    int bin_len;
    int len;

    for (bin_len = 0; cmd[bin_len]; bin_len++) {
        if (cmd[bin_len] == ' ' || cmd[bin_len] == '\t')
            break;
    }
    for (alias_t *al = env->alias; al; al = al->next) {
        if (!strncmp(al->alias, cmd, bin_len)) {
            len = strlen(cmd) + strlen(al->command) + 1 - bin_len;
            rm_n_char(cmd, bin_len);
            cmd = realloc(cmd, len);
            if (!cmd)
                return (NULL);
            insert_substring(cmd, al->command, 1);
        }
    }
    return (cmd);
}

char **parse_input(char *cmd, env_t *env, wordexp_t *parser)
{
    if (!(cmd = strdup(cmd + count_trailing_spaces(cmd))))
        return (NULL);
    if (!(cmd = process_vars(cmd, env)))
        return (NULL);
    cmd = process_aliases(cmd, env);
    switch (wordexp(cmd, parser, WRDE_SHOWERR)) {
    case 0:
        break;
    case WRDE_BADCHAR:
        dprintf(2, "Illegal occurrence of one of |, &, ;, <, >, (, ), {, }.\n");
        return (NULL);
    case WRDE_SYNTAX:
        dprintf(2, "Shell syntax error\n");
        return (NULL);
    default:
        dprintf(2, "Unknonw parsing error.\n");
        return (NULL);
    }
    free(cmd);
    return (parser->we_wordv);
}