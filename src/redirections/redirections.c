/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** redirections
*/

#include "my.h"
#include "shell.h"
#include "redirections.h"
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>

int get_input_redirect_fd(redirection *input)
{
    char **args = get_argv(input->arg);
    char *arg;
    int fd;

    if (!args)
        return (-1);
    arg = args[0];
    free(args);
    fd = open(arg, O_RDONLY);
    if (fd < 0) {
        perror(arg);
        return (-1);
    }
    return (fd);
}

int get_append_input_redirect_fd(redirection *input)
{
    return (input->fd);
}

int get_output_redirect_fd(redirection *output)
{
    char **args = get_argv(output->arg);
    char *arg;
    int fd;

    if (!args)
        return (-1);
    arg = args[0];
    free(args);
    fd = open(arg, O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror(arg);
        return (-1);
    }
    return (fd);
}

int get_append_output_redirect_fd(redirection *output)
{
    char **args = get_argv(output->arg);
    char *arg;
    int fd;

    if (!args)
        return (-1);
    arg = args[0];
    free(args);
    fd = open(arg, O_RDWR | O_CREAT | O_APPEND, 0644);
    if (fd < 0) {
        perror(arg);
        return (-1);
    }
    return (fd);
}

int get_pipe_fd(redirection *output)
{
    return (output->fd);
}