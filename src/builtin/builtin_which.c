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

char **get_paths_from_envpath(char *cmd, char **envpath)
{
    int len = 0;
    char **res = NULL;

    for (; envpath[len]; len++);
    res = malloc(sizeof(char *) * (len + 2));
    if (!res)
        return (NULL);
    fill_path_arr(cmd, envpath, res);
    return (res);
}

void print_alias_which(char *cmd, char *aliased)
{
    if (aliased[0] == '(') {
        aliased = &aliased[1];
        aliased[strlen(aliased) - 1] = 0;
    }
    printf("%s:\taliased to %s\n", cmd, aliased);
}

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

void print_path(char *cmd, char **envpath, env_t *env)
{
    char **res = NULL;
    char *dup_cmd = strdup(cmd);
    int len = 0;
    char *aliased = get_alias_command(cmd, env->alias);

    if (strcmp(aliased, dup_cmd)) {
        print_alias_which(dup_cmd, aliased);
        return;
    }
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
        print_path(argv[i], envpath, env);
    free(envpath);
    return (0);
}