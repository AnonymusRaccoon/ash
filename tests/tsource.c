/*
** EPITECH PROJECT, 2020
** ash
** File description:
** test source function
*/

#include <criterion/criterion.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "shell.h"
#include "builtin.h"

Test(parse_source_cmd, no_args)
{
    char *cmd = strdup("echo wow");
    char **argv = get_argv(strdup("source source_file"));
    int argv_len = 0;
    char *res = NULL;

    for (; argv[argv_len]; argv_len++);
    res = parse_source_cmd(cmd, argv, argv_len);
    cr_assert_str_eq(res, "echo wow");
}

Test(parse_source_cmd, one_arg)
{
    char *cmd = strdup("echo $1");
    char **argv = get_argv(strdup("source source_file wow"));
    int argv_len = 0;
    char *res = NULL;

    for (; argv[argv_len]; argv_len++);
    res = parse_source_cmd(cmd, argv, argv_len);
    cr_assert_str_eq(res, "echo wow");
}

Test(parse_source_cmd, two_args)
{
    char *cmd = strdup("$2 $1");
    char **argv = get_argv(strdup("source source_file wow echo"));
    int argv_len = 0;
    char *res = NULL;

    for (; argv[argv_len]; argv_len++);
    res = parse_source_cmd(cmd, argv, argv_len);
    cr_assert_str_eq(res, "echo wow");
}

Test(parse_source_cmd, args_out_of_range)
{
    char *cmd = strdup("echo wow$1");
    char **argv = get_argv(strdup("source source_file"));
    int argv_len = 0;
    char *res = NULL;

    for (; argv[argv_len]; argv_len++);
    res = parse_source_cmd(cmd, argv, argv_len);
    cr_assert_str_eq(res, "echo wow");
}

Test(parse_source_cmd, args_index_0)
{
    char *cmd = strdup("echo shell is: $0");
    char **argv = get_argv(strdup("source source_file"));
    int argv_len = 0;
    char *res = NULL;

    for (; argv[argv_len]; argv_len++);
    res = parse_source_cmd(cmd, argv, argv_len);
    cr_assert_str_eq(res, "echo shell is: 42sh");
}

Test(parse_source_cmd, args_inside_cmd)
{
    char *cmd = strdup("e$1o wow");
    char **argv = get_argv(strdup("source source_file ch"));
    int argv_len = 0;
    char *res = NULL;

    for (; argv[argv_len]; argv_len++);
    res = parse_source_cmd(cmd, argv, argv_len);
    cr_assert_str_eq(res, "echo wow");
}

Test(parse_source_cmd, invalid_arg)
{
    char *cmd = strdup("e$o wow");
    char **argv = get_argv(strdup("source source_file ch"));
    int argv_len = 0;
    char *res = NULL;

    for (; argv[argv_len]; argv_len++);
    res = parse_source_cmd(cmd, argv, argv_len);
    cr_assert_str_eq(res, "e wow");
}

Test(parse_source_cmd, empty_str)
{
    char *cmd = strdup("");
    char **argv = get_argv(strdup("source source_file ch"));
    int argv_len = 0;
    char *res = NULL;

    for (; argv[argv_len]; argv_len++);
    res = parse_source_cmd(cmd, argv, argv_len);
    cr_assert_str_eq(res, "");
}