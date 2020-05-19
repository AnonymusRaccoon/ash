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
    argv = split_args(cmd, argv);
    return (argv);
}

char **split_args(char *cmd, char **argv)
{
    int i = 0;
    int j = 0;
    int nb_simple = 0;
    int nb_double = 0;

    for (i = 0; cmd[i]; i++) {
        i += cmd[i] == '\\' ? 2 : 0;
        nb_simple += cmd[i] == '\'' ? 1 : 0;
        nb_double += cmd[i] == '\"' ? 1 : 0;
        if ((nb_double % 2 == 1 || nb_simple % 2 == 1)
            || (cmd[i] != ' ' && cmd[i] != '\t'))
            continue;
        cmd[i] = '\0';
        if (i > 0)
            argv[j++] = cmd;
        cmd += i + 1;
        i = -1;
    }
    if (i > 0)
        argv[j++] = cmd;
    return (argv);
}

