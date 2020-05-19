/*
** EPITECH PROJECT, 2020
** ash
** File description:
** glob
*/

#include <glob.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "shell.h"

char **glob_error(char **argv, int err)
{
    if (err == GLOB_ABORTED)
        fprintf(stderr, "%s: %s\n", argv[0], "Aborted.");
    if (err == GLOB_NOMATCH)
        fprintf(stderr, "%s: %s\n", argv[0], "No match.");
    if (err == GLOB_NOSPACE)
        fprintf(stderr, "%s: %s\n", argv[0], "No space.");
    free(argv);
    return (NULL);
}

char **globbing(char **argv)
{
    static glob_t results;
    int flags = GLOB_DOOFFS | GLOB_NOMAGIC;
    int ret = 0;

    for (int i = 0; argv[i] && ret == 0; i++) {
        flags |= (i > 0 ? GLOB_APPEND : 0);
        ret = glob(argv[i], flags, NULL, &results);
    }
    if (ret != 0) {
        globfree(&results);
        return (glob_error(argv, ret));
    }
    free(argv);
    return (&results.gl_pathv[0]);
}