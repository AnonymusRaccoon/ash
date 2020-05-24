/*
** EPITECH PROJECT, 2020
** 42sh
** File description:
** if builtin
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "shell.h"
#include "builtin.h"

int matched_parenthesis(char **argv)
{
    int left_p = 0;
    int right_p = 0;

    for (int i = 0; argv[i]; i++)
        for (int j = 0; argv[i][j]; j++) {
            left_p = argv[i][j] == '(' ? left_p + 1 : left_p;
            right_p = argv[i][j] == ')' ? right_p + 1 : right_p;
        }
    if (left_p > right_p)
        printf("Too many ('s.\n");
    if (right_p > left_p)
        printf("Too many )'s.\n");
    if (left_p == right_p)
        return (1);
    return (0);
}

int get_max_cmd_len(char **argv)
{
    int len = 0;

    for (int i = 0; argv[i]; i++) {
        if (i)
            len++;
        for (int j = 0; argv[i][j]; j++)
            len++;
    }
    return (len);
}

int execute_one_liner(char **argv, env_t *env)
{
    bool after_exp = false;
    char *cmd = malloc(sizeof(char) * get_max_cmd_len(argv));
    int counter = 0;

    if (!cmd || get_test_return_value(argv, env))
        return (0);
    for (int i = 0; argv[i]; i++) {
        for (int j = 0; argv[i][j]; j++) {
            if (after_exp)
                cmd[counter++] = argv[i][j];
            if (argv[i][j] == ')')
                after_exp = true;
        }
        if (after_exp && counter)
            cmd[counter++] = ' ';
    }
    cmd[counter] = 0;
    eval_raw_cmd(cmd, env);
    free(cmd);
    return (0);
}

int is_valid_if_cmd(char **argv)
{
    int len = 0;

    for (; argv[len]; len++);
    if (len < 1) {
        printf("if: Too few arguments\n");
        return (0);
    }
    if (!matched_parenthesis(argv))
        return (0);
    if (argv[1][0] != '(') {
        printf("if: Expression Syntax.\n");
        return (0);
    }
    return (1);
}

int builtin_if(char **argv, env_t *env)
{
    if (is_valid_if_cmd(argv)) {
        execute_one_liner(argv, env);
        env->vars = my_setenv(env->vars, "?", "0");
    } else
        env->vars = my_setenv(env->vars, "?", "1");
    return (0);
}