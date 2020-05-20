/*
** EPITECH PROJECT, 2020
** ash
** File description:
** builtin where
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "builtin.h"
#include "utility.h"
#include "shell.h"

void print_alias_where(char *cmd, char *aliased)
{
    if (aliased[0] == '(') {
        aliased = &aliased[1];
        aliased[strlen(aliased) - 1] = 0;
    }
    printf("%s is aliased to %s\n", cmd, aliased);
}

char *check_executable(char *cmd, char *folder)
{
    struct stat st_buff;
    char *path = catpath(folder, cmd);
    char *res = path;

    if (stat(path, &st_buff) == -1)
        res = NULL;
    if (access(path, F_OK))
        res = NULL;
    if (access(path, X_OK))
        res = NULL;
    if ((st_buff.st_mode & __S_IFMT) == __S_IFDIR)
        res = NULL;
    if (!res)
        free(path);
    return (res);
}

void fill_path_arr(char *cmd, char **envpath, char **res)
{
    int counter = 0;
    char *path = NULL;

    if (strchr(cmd, '/') == NULL) {
        if (!envpath)
            return;
        for (int i = 0; envpath[i]; i++) {
            path = check_executable(cmd, envpath[i]);
            if (path) {
                res[counter++] = path;
            }
        }
    }
    else {
        path = check_executable(cmd, "");
        if (path) {
            res[counter++] = path;
        }
    }
    res[counter] = NULL;
}

void print_path_no_stop(char *cmd, char **envpath, env_t *env)
{
    char *dup_cmd = strdup(cmd);
    char **paths = NULL;
    char *aliased = get_alias_command(cmd, env->alias);

    if (strcmp(aliased, dup_cmd))
        print_alias_where(dup_cmd, aliased);
    find_path_in_builtins(cmd);
    if (!envpath)
        return;
    paths = get_paths_from_envpath(cmd, envpath);
    if (!paths)
        return;
    for (int i = 0; paths[i]; i++)
        printf("%s\n", paths[i]);
    destroy_str_arr(paths);
}

int builtin_where(char **argv, env_t *env)
{
    int len = 0;
    char **envpath = NULL;

    for (; argv[len]; len++);
    if (len <= 1) {
        printf("where: Too few arguments.\n");
        return (0);
    }
    envpath = get_envpath(env);
    for (int i = 1; argv[i]; i++) {
        if (strchr(argv[i], '/'))
            printf("where: / in command makes no sense\n");
        else
            print_path_no_stop(argv[i], envpath, env);
    }
    free(envpath);
    return (0);
}