/*
** EPITECH PROJECT, 2020
** ash
** File description:
** builtin which
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "shell.h"
#include "utility.h"
#include "builtin.h"

bool find_path_in_builtins(char *cmd)
{
    extern const builtin builtins[];

    for (int i = 0; builtins[i].name; i++)
        if (!strcmp(cmd, builtins[i].name)) {
            printf("%s: shell built-in command.\n", cmd);
            return (true);
        }
    return (false);
}

void print_path(char *cmd, char **envpath)
{
    char **res = NULL;
    int len = 0;
    //check_alias
    if (find_path_in_builtins(cmd))
        return;
    res = get_paths_from_envpath(cmd, envpath);
    for (; res[len]; len++);
    if (len)
        printf("%s\n", res[0]);
    else
        printf("%s: Command not found.\n", cmd);
    destroy_str_arr(res);
}

int builtin_which(char **argv, env_t *env)
{
    int len = 0;
    char **envpath = NULL;

    for (; argv[len]; len++);
    if (len == 1) {
        printf("%s: Too few arguments.\n", argv[0]);
        return (0);
    }
    envpath = get_envpath(env);
    for (int i = 1; argv[i]; i++)
        print_path(argv[i], envpath);
    free(envpath);
    return (0);
}