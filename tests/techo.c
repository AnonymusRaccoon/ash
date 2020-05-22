/*
** EPITECH PROJECT, 2020
** test_echo.c
** File description:
** techo
*/

#include <criterion/redirect.h>
#include <criterion/criterion.h>
#include "builtin.h"

Test(echo, normal_message, .init = cr_redirect_stdout)
{
    env_t env = {};
    char *av[] = {"echo", "hello", NULL};
    builtin_echo(av, &env);
    cr_assert_stdout_eq_str("hello\n");
}

Test(echo, with_simple_backslash, .init = cr_redirect_stdout)
{
    env_t env = {};
    char *av[] = {"echo", "\\n", NULL};
    builtin_echo(av, &env);
    cr_assert_stdout_eq_str("\n\n");
}

Test(echo, incorrect_ascii, .init = cr_redirect_stdout)
{
    env_t env = {};
    char *av[] = {"echo", "\\q", NULL};
    builtin_echo(av, &env);
    cr_assert_stdout_eq_str("\\q\n");
}

Test(echo, multiple_args, .init = cr_redirect_stdout)
{
    env_t env = {};
    char *av[] = {"echo", "Hello", "I\'m", "Marvin", NULL};
    builtin_echo(av, &env);
    cr_assert_stdout_eq_str("Hello I\'m Marvin\n");
}