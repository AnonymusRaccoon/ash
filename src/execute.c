/*
** EPITECH PROJECT, 2020
** PSU_minishell1_2019
** File description:
** execute
*/

#include <sys/stat.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <malloc.h>
#include <signal.h>
#include <errno.h>
#include "utility.h"
#include "shell.h"
#include "redirections.h"

char *find_binary(char *cmd, char *folder)
{
    char *path = catpath(folder, cmd);

    if (access(path, F_OK)) {
        free(path);
        return (NULL);
    }
    return (path);
}

char *eval(char *cmd, char **argv, env_t* env)
{
    char *pathstr= my_getenv(env->env, "PATH");
    char *path = NULL;
    char **envpath = NULL;

    if (pathstr) {
        pathstr = strdup(pathstr);
        if (pathstr)
            envpath = to_array(pathstr);
    }
    if (strchr(cmd, '/') == NULL) {
        if (!envpath)
            return (NULL);
        for (int i = 0; envpath[i] && !path; i++)
            path = find_binary(cmd, envpath[i]);
    } else
        path = cmd;
    execve(path, argv, env->env);
    return (path);
}

bool handle_redirections(redirection *inout[2], env_t *env, bool builtin)
{
    int fd;

    if (inout[0]) {
        if (inout[0]->type->run_cmd && !(inout[0]->type->type & PIPE))
            inout[0]->type->run_cmd(inout[0], env);
        if ((fd = inout[0]->type->get_fd(inout[0])) == -1)
            return (true);
        dup2(fd, 0);
        close(fd);
        if (inout[0]->type->type & EX_PIPE && !builtin)
            close(inout[0]->extra_data);
    }
    if (inout[1]) {
        if ((fd = inout[1]->type->get_fd(inout[1])) == -1)
            return (true);
        dup2(fd, 1);
        close(fd);
        if (inout[1]->type->type & EX_PIPE && !builtin)
            close(inout[1]->extra_data);
    }
    return (false);
}

bool handle_parent_inout(redirection *inout[2], env_t *env, bool builtin)
{
    if (inout[0] && inout[0]->type->type & EX_PIPE && !builtin) {
        if (!fd_is_used(inout[0]->fd, inout[1]))
            close(inout[0]->fd);
        if (!fd_is_used(inout[0]->extra_data, inout[1]))
            close(inout[0]->extra_data);
    }
    if (inout[1] && inout[1]->type->run_cmd) {
        inout[1]->type->run_cmd(inout[1], env);
        return (true);
    }
    return (false);
}

void run_cmd(char **argv, redirection *inout[2], env_t *env)
{
    pid_t pid;
    int status;
    char *path;

    if (strlen(argv[0]) == 0)
        return;
    pid = fork();
    if (pid == 0) {
        if (handle_redirections(inout, env, false))
            exit(1);
        path = eval(argv[0], argv, env);
        return (exec_error(path, argv[0]));
    }
    if (handle_parent_inout(inout, env, false))
        return;
    waitpid(pid, &status, 0);
    handle_signal(status, env);
}