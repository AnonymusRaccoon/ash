/*
** EPITECH PROJECT, 2020
** PSU_minishell1_2019
** File description:
** env
*/

#include <criterion/criterion.h>
#include "shell.h"

Test(setenv, normal)
{
    char **env = malloc(sizeof(char **) * 1);
    env[0] = NULL;
    env = my_setenv(env, "enorme", "TEST");

    cr_assert_str_eq(env[0], "enorme=TEST");
    cr_assert_eq(env[1], NULL);
}

Test(setenv, null)
{
    char **env = malloc(sizeof(char **) * 1);
    env[0] = NULL;
    env = my_setenv(env, "enorme", NULL);

    cr_assert_str_eq(env[0], "enorme=");
    cr_assert_eq(env[1], NULL);
}

Test(env, unsetenv)
{
    char **env = malloc(sizeof(char **) * 1);
    env[0] = NULL;
    env = my_setenv(env, "enorme", "TEST");

    cr_assert_str_eq(env[0], "enorme=TEST");
    cr_assert_eq(env[1], NULL);

    env = my_unsetenv(env, "enorme");
    cr_assert_eq(env[0], NULL);
}