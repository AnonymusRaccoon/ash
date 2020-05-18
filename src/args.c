/*
** EPITECH PROJECT, 2020
** PSU_minishell1_2019
** File description:
** args
*/

#include <unistd.h>
#include <malloc.h>
#include <stdbool.h>
#include <string.h>
#include <shell.h>

int get_arg_count(char *cmd)
{
    int count = 0;

    for (int i = 0; cmd[i]; i++) {
        if (cmd[i] == ' ')
            count++;
    }
    return (count);
}

char **get_argv(char *cmd)
{
    char **argv = calloc(get_arg_count(cmd) + 2, sizeof(char *));

    if (!argv)
        return (NULL);
    argv = split_args(cmd, argv, 0, 0);
    return (argv);
}

char **split_args(char *cmd, char **argv, int nb_simple, int nb_double)
{
    int i = 0;
    int j = 0;

    for (i = 0; cmd[i]; i++) {
        if (cmd[i] == '\\')
            i += 2;
        nb_simple += cmd[i] == '\'' ? 1 : 0;
        nb_double += cmd[i] == '\"' ? 1 : 0;
        if ((nb_double % 2 == 1 || nb_simple % 2 == 1)
            || (cmd[i] != ' ' && cmd[i] != '\t'))
            continue;
        cmd[i] = '\0';
        if (i > 0)
            argv[j++] = remove_backslash(cmd);
        cmd += i + 1;
        i = -1;
    }
    if (i > 0)
        argv[j++] = remove_backslash(cmd);
    return (argv);
}

char *remove_backslash(char *cmd)
{
    for (int i = 0; cmd[i]; i++) {
        if (cmd[i] != '\\')
            continue;
        if (cmd[i + 1] == 'n')
            cmd[i + 1] = '\n';
        if (cmd[i + 1] == 'b')
            cmd[i + 1] = '\b';
        if (cmd[i + 1] == 't')
            cmd[i + 1] = '\t';
        if (cmd[i + 1] == 'v')
            cmd[i + 1] = '\v';
        if (cmd[i + 1] != 'v' && cmd[i + 1] != 'n'
            && cmd[i + 1] != 'b' && cmd[i + 1] != 't')
            cmd[i] = cmd[i + 1];
        for (int k = i; cmd[k]; k++)
            cmd[k] = cmd[k + 1];
    }
    return (cmd);
}

char **remove_quotes(char **argv)
{
    int len = 0;
    for (int i = 0; argv[i]; i++) {
        len = strlen(argv[i]);
        if ((argv[i][0] == '\"' && argv[i][len - 1] == '\"')
        || (argv[i][0] == '\'' && argv[i][len - 1] == '\'')) {
            argv[i][len - 1] = 0;
            argv[i]++;
        }
    }
    return (argv);
}