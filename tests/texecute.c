/*
** EPITECH PROJECT, 2020
** PSU_minishell1_2019
** File description:
** texecute
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "shell.h"

char *eval(char *cmd, char **argv, env_t* env);

extern char **environ;

Test(execute, get_path, .init = cr_redirect_stdout)
{
    env_t *env = malloc(sizeof(env_t));
    env->vars = NULL;
    env->env = environ;
    char **argv = get_argv("ls");

    eval("ls", argv, env);
    cr_assert_fail();
}

// Disabled since github does not have ls in the /usr/bin/ls path.
// Test(execute, absolute, .init = cr_redirect_stdout)
// {
//     env_t *env = malloc(sizeof(env_t));
//     env->vars = NULL;
//     env->env = environ;
//     char **argv = get_argv("/usr/bin/ls");

//     eval(argv[0], argv, env);
//     cr_assert_fail();
// }

Test(execute, notfound, .init = cr_redirect_stderr)
{
    env_t *env = malloc(sizeof(env_t));
    env->vars = NULL;
    env->env = environ;

    run_cmd((char *[]){"mkjzb", NULL}, (redirection *[2]){NULL, NULL}, env);
    cr_assert_stderr_eq_str("mkjzb: Command not found.\n");
}