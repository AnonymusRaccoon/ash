/*
** EPITECH PROJECT, 2020
** PSU_minishell1_2019
** File description:
** args
*/


#include <unistd.h>
#include <malloc.h>

int get_arg_count(char *cmd)
{
    int count = 0;

    for (int i = 0; cmd[i]; i++) {
        if (cmd[i] == ' ')
            count++;
    }
    return (count);
}

int get_argc(char **argv)
{
    int i = 0;

    while (argv[i])
        i++;
    return (i);
}

char **get_argv(char *cmd)
{
    char **argv = malloc(sizeof(char *) * (get_arg_count(cmd) + 2));
    int i;
    int j = 0;

    for (i = 0; cmd[i]; i++) {
        if (cmd[i] != ' ' && cmd[i] != '\t')
            continue;
        cmd[i] = '\0';
        if (i > 0) {
            argv[j] = cmd;
            j++;
        }
        cmd += i + 1;
        i = -1;
    }
    if (i > 0) {
        argv[j] = cmd;
        j++;
    }
    argv[j] = NULL;
    return (argv);
}