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

char *check_executable(char *cmd, char *folder)
{
    struct stat st_buff;
    char *path = catpath(folder, cmd);

    if (stat(path, &st_buff) == -1)
        return (NULL);
    if (access(path, F_OK)) {
        return (NULL);
    }
    if (access(path, X_OK)) {
        return (NULL);
    }
    if ((st_buff.st_mode & __S_IFMT) == __S_IFDIR) {
        return (NULL);
    }
    return (path);
}

char **get_envpath(env_t *env)
{
    char **envpath = NULL;
    char *pathstr = my_getenv(env->env, "PATH");
    char *path_cpy = NULL;

    if (pathstr) {
        path_cpy = strdup(pathstr);
        envpath = to_array(path_cpy);
        free(path_cpy);
    }
    return (envpath);
}

bool find_paths_from_env(char *cmd, env_t *env)
{
    bool res = false;
    char *path = NULL;
    char **envpath = get_envpath(env);

    if (strchr(cmd, '/') == NULL) {
        if (!envpath)
            return (res);
        for (int i = 0; envpath[i]; i++) {
            path = check_executable(cmd, envpath[i]);
            if (path) {
                printf("%s\n", path);
                res = true;
            }
        }
    }
    else if (check_executable(cmd, "")) {
        printf("%s\n", cmd);
        res = true;
    }
    return (res);
}

void print_path_no_stop(char *cmd, env_t *env)
{
    //check_alias_no_stop
    find_path_in_builtins(cmd);
    find_paths_from_env(cmd, env);
}

int builtin_where(char **argv, env_t *env)
{
    int len = 0;

    if (!argv)
        return (0);
    for (; argv[len]; len++);
    if (len <= 1) {
        printf("where: Too few arguments.\n");
        return (0);
    }
    for (int i = 1; argv[i]; i++) {
        if (strchr(argv[i], '/'))
            printf("where: / in command makes no sense\n");
        else
            print_path_no_stop(argv[i], env);
    }
    return (0);
}