/*
** EPITECH PROJECT, 2020
** ash
** File description:
** envpath
*/

#include <string.h>
#include "utility.h"
#include "shell.h"
#include <stdlib.h>

void destroy_str_arr(char **arr)
{
    if (arr) {
        for (int i = 0; arr[i]; i++)
            free(arr[i]);
        free(arr);
    }
}

char **get_envpath(env_t *env)
{
    char **envpath = NULL;
    char *pathstr = my_getenv(env->env, "PATH");
    char *path_cpy = NULL;

    if (pathstr) {
        path_cpy = strdup(pathstr);
        envpath = to_array(path_cpy);
    }
    return (envpath);
}