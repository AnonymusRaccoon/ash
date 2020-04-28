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

int check_builtins(char *cmd)
{
    const builtin builtin_arr[] = {
        {"env", &builtin_env},
        {"setenv", &builtin_setenv},
        {"unsetenv", &builtin_unsetenv},
        {"exit", &builtin_exit},
        {"cd", &builtin_cd},
        {"which", NULL},
        {"where", NULL},
        {NULL, NULL}
    };
    for (int i = 0; builtin_arr[i].name; i++)
        if (!strcmp(cmd, builtin_arr[i].name)) {
            printf("%s: shell built-in command.\n", cmd);
            return (1);
        }
    return (0);
}

int check_path(char *cmd, env_t *env)
{
    char *path = NULL;
    char **envpath = get_envpath(env);

    if (strchr(cmd, '/') == NULL) {
        if (!envpath)
            return (0);
        for (int i = 0; envpath[i] && !path; i++) {
            path = check_executable(cmd, envpath[i]);
            if (path) {
                printf("%s\n", path);
                return (1);
            }
        }
    }
    else if (check_executable(cmd, "")) {
        printf("%s\n", cmd);
        return (1);
    }
    return (0);
}

void print_path(char *cmd, env_t *env)
{
    //check_alias
    if (check_builtins(cmd))
        return;
    if (check_path(cmd, env))
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