/*
** EPITECH PROJECT, 2020
** ash
** File description:
** builtin which
*/

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

bool find_path_from_env(char *cmd, env_t *env)
{
    char *path = NULL;
    char **envpath = get_envpath(env);

    if (strchr(cmd, '/') == NULL) {
        if (!envpath)
            return (false);
        for (int i = 0; envpath[i] && !path; i++) {
            path = check_executable(cmd, envpath[i]);
            if (path) {
                printf("%s\n", path);
                return (true);
            }
        }
    }
    else if (check_executable(cmd, "")) {
        printf("%s\n", cmd);
        return (true);
    }
    return (false);
}

void print_path(char *cmd, env_t *env)
{
    //check_alias
    if (find_path_in_builtins(cmd))
        return;
    if (find_path_from_env(cmd, env))
        return;
    else
        printf("%s: Command not found.\n", cmd);
}

int builtin_which(char **argv, env_t *env)
{
    int len = 0;

    if (!argv)
        return (0);
    for (; argv[len]; len++);
    if (len == 1) {
        printf("%s: Too few arguments.\n", argv[0]);
        return (0);
    }
    for (int i = 1; argv[i]; i++)
        print_path(argv[i], env);
    return (0);
}