/*
** EPITECH PROJECT, 2020
** ash
** File description:
** builtin where
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "builtin.h"
#include "utility.h"
#include "shell.h"

char **get_envpath(env_t *env)
{
    char **envpath = NULL;
    char *pathstr = my_getenv(env->env, "PATH");

    if (pathstr) {
        pathstr = strdup(pathstr);
        if (pathstr)
            envpath = to_array(pathstr);
    }
    if (pathstr)
        free(pathstr);
    return (envpath);
}

int check_path_no_stop(char *cmd, env_t *env)
{
    int res = 0;
    char *path = NULL;
    char **envpath = get_envpath(env);

    if (strchr(cmd, '/') == NULL) {
        if (!envpath)
            return (0);
        for (int i = 0; envpath[i]; i++) {
            path = find_binary(cmd, envpath[i]);
            if (path) {
                printf("%s\n", path);
                res++;
            }
        }
    }
    else if (find_binary(cmd, "")) {
        printf("%s\n", cmd);
        res++;
    }
    return (res);
}

void print_path_no_stop(char *cmd, env_t *env)
{
    //check_alias_no_stop
    check_builtins(cmd);
    check_path_no_stop(cmd, env);
}

int builtin_where(char **argv, env_t *env)
{
    int len = 0;

    if (!argv)
        return (0);
    for (; argv[len]; len++);
    if (len <= 1)
        return (0);
    for (int i = 1; argv[i]; i++) {
        if (strchr(argv[i], '/'))
            printf("where: / in command makes no sense\n");
        else
            print_path_no_stop(argv[i], env);
    }
    return (0);
}