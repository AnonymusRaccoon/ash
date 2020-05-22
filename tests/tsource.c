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
#include "utility.h"
#include "builtin.h"

Test(get_special_arg_at, at_arg)
{
    char **argv = split_str(strdup("source file a b c"), ' ');
    int argv_len = 5;
    char *res = NULL;

    for (; argv[argv_len]; argv_len++);
    res = get_special_arg_at(argv, argv_len);
    cr_assert_str_eq(res, "\"a\" \"b\" \"c\"");
}

Test(get_special_arg_star, at_arg)
{
    char **argv = split_str(strdup("source file a b c"), ' ');
    int argv_len = 5;
    char *res = NULL;

    for (; argv[argv_len]; argv_len++);
    res = get_special_arg_star(argv, argv_len);
    cr_assert_str_eq(res, "\"a b c\"");
}