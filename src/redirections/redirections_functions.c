/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** redirections_input
*/


#include "shell.h"
#include "redirections.h"
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

void redirection_ctr(redirection *red, char *cmd, const redirection_map *type)
{
    int fd[2];

    red->type = type;
    red->arg = cmd;
    red->fd = -1;
    if (type->type & EX_PIPE) {
        if (pipe(fd) != 0) {
            perror("mysh");
            red->fd = -1;
            red->extra_data = -1;
            return;
        }
        red->fd = fd[1];
        red->extra_data = fd[0];
    }
}

bool fd_is_used(int fd, redirection *inout)
{
    if (!inout)
        return (false);
    return (inout->fd == fd || inout->extra_data == fd);
}

void handle_pipe(redirection *command, env_t *env)
{
    int tmp = command->fd;

    command->fd = command->extra_data;
    command->extra_data = tmp;
    run_with_redirections(command->arg, env, command);
}

void handle_eof_input(redirection *in, env_t *env)
{
    char **args = get_argv(in->arg);
    char *input = NULL;
    size_t t = 0;
    char *eof;
    int tmp = in->fd;

    in->fd = in->extra_data;
    in->extra_data = tmp;
    if (!args)
        return;
    eof = malloc(sizeof(char) * (strlen(args[0]) + 2));
    strcpy(eof, args[0]);
    strcpy(eof + strlen(args[0]), "\n");
    write(1, "? ", 2);
    while (getline(&input, &t, stdin) >= 0) {
        if (!strcmp(input, eof))
            return;
        write(in->extra_data, input, strlen(input));
        write(1, "? ", 2);
    }
    (void)env;
}