/*
** EPITECH PROJECT, 2020
** ash
** File description:
** glob
*/

#include <glob.h>
#include <stdio.h>
#include <unistd.h>
#include "shell.h"

int glob_error(char *arg, int err)
{
    if (err == GLOB_ABORTED)
        fprintf(stderr, "%s: %s\n", arg, "Aborted.");
    if (err == GLOB_NOMATCH)
        fprintf(stderr, "%s: %s\n", arg, "No match.");
    if (err == GLOB_NOSPACE)
        fprintf(stderr, "%s: %s\n", arg, "No space.");
    return (ERROR);
}

int globbing(char *path, char **argv, env_t *env)
{
    static glob_t results;
    static int flags = 0;
    static int ret = 0;

    if (get_argc(argv) == 1)
        return (execve(path, argv, env->env));
    results.gl_offs = 1;
    for (int i = 1; argv[i] && ret == 0; i++) {
        flags = (i > 1 ? GLOB_DOOFFS | GLOB_APPEND : GLOB_DOOFFS);
        ret = glob(argv[i], flags, NULL, &results);
    }
    if (ret != 0)
        return (glob_error(argv[0], ret));
    results.gl_pathv[0] = path;
    execve(path, &results.gl_pathv[0], env->env);
    globfree(&results);
    return (0);
}
