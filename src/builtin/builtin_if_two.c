/*
** EPITECH PROJECT, 2020
** 42sh
** File description:
** builtin_if_two
*/

#include <string.h>
#include <stdlib.h>
#include "shell.h"
#include "builtin.h"

char *get_expr(char **argv)
{
    bool in_expr = false;
    char *res = malloc(sizeof(char) * get_max_cmd_len(argv) + 5);
    int counter = 5;

    if (!res) return (NULL);
    strcpy(res, "test ");
    for (int i = 0; argv[i]; i++) {
        for (int j = 0; argv[i][j]; j++) {
            if (argv[i][j] == ')')
                in_expr = false;
            if (in_expr)
                res[counter++] = argv[i][j];
            if (argv[i][j] == '(')
                in_expr = true;
        }
        if (in_expr && counter)
            res[counter++] = ' ';
    }
    res[counter] = 0;
    return (res);
}

int get_test_return_value(char **argv, env_t *env)
{
    int res = 0;
    char *exp = get_expr(argv);

    eval_raw_cmd(exp, env);
    res = my_getenv(env->vars, "?") ? atoi(my_getenv(env->vars, "?")) : 1;
    free(exp);
    return (res);
}