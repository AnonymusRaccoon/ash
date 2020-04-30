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

int run_builtin(const builtin *cmd, char **a, redirection *inout[2], env_t *env)
{
    int ret = 0;
    int saved_fd[2];

    saved_fd[0] = dup(0);
    saved_fd[1] = dup(1);
    if (saved_fd[0] < 0 || saved_fd[1] < 0) {
        perror("mysh");
        return (-1);
    }
    if (!handle_redirections(inout, env, true))
        ret = cmd->run(a, env);
    dup2(saved_fd[0], 0);
    dup2(saved_fd[1], 1);
    close(saved_fd[0]);
    close(saved_fd[1]);
    if (handle_parent_inout(inout, env, true))
        ret = 0;
    return (ret);
}

int builtin_cd(char **argv, env_t *env)
{
    char *path = NULL;
    char *old = getcwd(NULL, 0);

    if (get_argc(argv) > 2) {
        write(2, "cd: Too many arguments.\n", 25);
        free(argv);
        return (0);
    }
    if (!argv[1])
        path = my_getenv(env->env, "HOME");
    else if (argv[1] && !strcmp(argv[1], "-"))
        path = my_getenv(env->env, "OLDPWD");
    else
        path = argv[1];
    if (chdir(path) < 0)
        printf("%s: %s.\n", path, strerror(errno));
    else
        env->env = my_setenv(env->env, "OLDPWD", old);
    free(old);
    free(argv);
    return (0);
}

int builtin_exit(char **argv, env_t *env)
{
    free(argv);
    (void)env;
    return (-1);
}
