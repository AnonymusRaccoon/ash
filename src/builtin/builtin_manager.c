/*
** EPITECH PROJECT, 2020
** PSU_minishell1_2019
** File description:
** builtin
*/

#include "shell.h"
#include "builtin.h"
#include "redirections.h"
#include <unistd.h>
#include <malloc.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int run_builtin(const builtin *cmd, char **a, redirection *inout[2], env_t *env)
{
    int ret = 0;
    int saved_fd[3];

    saved_fd[0] = dup(0);
    saved_fd[1] = dup(1);
    saved_fd[2] = dup(2);
    if (saved_fd[0] < 0 || saved_fd[1] < 0) {
        perror("mysh");
        return (-1);
    }
    if (!handle_redirections(inout, env, true))
        ret = cmd->run(a, env);
    dup2(saved_fd[0], 0);
    dup2(saved_fd[1], 1);
    dup2(saved_fd[2], 2);
    close(saved_fd[0]);
    close(saved_fd[1]);
    close(saved_fd[2]);
    if (handle_parent_inout(inout, env, true))
        ret = 0;
    return (ret);
}

int builtin_cd(char **argv, env_t *env)
{
    char *path = argv[1];
    char *old = getcwd(NULL, 0);

    if (get_argc(argv) > 2) {
        write(2, "cd: Too many arguments.\n", 25);
        env->vars = my_setenv(env->vars, "?", "1");
        return (0);
    }
    env->vars = my_setenv(env->vars, "?", "0");
    if (!argv[1])
        path = my_getenv(env->env, "HOME");
    else if (argv[1] && !strcmp(argv[1], "-"))
        path = my_getenv(env->env, "OLDPWD");
    if (chdir(path) < 0) {
        printf("%s: %s.\n", path, strerror(errno));
        env->vars = my_setenv(env->vars, "?", "1");
    } else
        env->env = my_setenv(env->env, "OLDPWD", old);
    free(old);
    return (0);
}

bool my_strisnum(char *str)
{
    for (int i = 0; str[i]; i++) {
        if (!isdigit(str[i]))
            return (false);
    }
    return (true);
}

int builtin_exit(char **argv, env_t *env)
{
    char *ptr = argv[1];

    if (!ptr)
        exit(0);
    if (argv[1][0] == '-') {
        ptr = &ptr[1];
    }
    if (!my_strisnum(ptr)) {
        dprintf(2, "exit: Expression Syntax.\n");
        return (0);
    }
    exit(atoi(argv[1]));
}