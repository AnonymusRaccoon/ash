/*
** EPITECH PROJECT, 2020
** PSU_minishell1_2019
** File description:
** argc
*/

#include <criterion/criterion.h>
#include "shell.h"

Test(args, noargs)
{
    char **args = get_argv(strdup("ls"));

    cr_assert_str_eq(args[0], "ls");
    cr_assert_eq(args[1], NULL);
}

Test(args, simplearg)
{
    char **args = get_argv(strdup("ls -l"));

    cr_assert_str_eq(args[0], "ls");
    cr_assert_str_eq(args[1], "-l");
    cr_assert_eq(args[2], NULL);
}

Test(args, trailingspace)
{
    char **args = get_argv(strdup("ls "));

    cr_assert_str_eq(args[0], "ls");
    cr_assert_eq(args[1], NULL);
}

Test(args, morespaces)
{
    char **args = get_argv(strdup("          ls    "));

    cr_assert_str_eq(args[0], "ls");
    cr_assert_eq(args[1], NULL);
}