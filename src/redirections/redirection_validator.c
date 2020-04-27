/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** redirection_validator
*/

#include "my.h"
#include "shell.h"
#include "redirections.h"
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>


bool validate_redirection_args(const redirection_map *cmd, char *arg, char *end)
{
    int count = 0;

    for (int i = 0; arg[i] && &arg[i] != end; i++)
        if (arg[i] != ' ' && arg[i] != '\t')
            count++;
    if (count != 0 && end - arg - 1 != 0)
        return (true);
    if (cmd->type & PIPE)
        my_printf("Invalid null command.\n");
    else
        my_printf("Missing name for redirect.\n");
    return (false);
}

bool redirections_are_ambiguous(const redirection_map *shell_cmd, \
int *input_count, int *output_count)
{
    *input_count += (shell_cmd->type & INPUT) != 0;
    *output_count += (shell_cmd->type & OUTPUT) != 0;
    if (*input_count > 1) {
        my_printf("Ambiguous input redirect.\n");
        return (true);
    }
    if (*output_count > 1) {
        my_printf("Ambiguous output redirect.\n");
        return (true);
    }
    if (shell_cmd->type & PIPE) {
        *input_count = 1;
        *output_count = 0;
    }
    return (false);
}

bool redirections_are_invalid(char *cmd)
{
    int input_count = 0;
    int output_count = 0;
    const redirection_map *shell_cmd = NULL;
    char *fcmd = cmd;

    do {
        if (!get_redirection(cmd))
            continue;
        shell_cmd = get_redirection(cmd);
        if (!validate_redirection_args(shell_cmd, fcmd, cmd))
            return (true);
        cmd += my_strlen(shell_cmd->key);
        if (redirections_are_ambiguous(shell_cmd, &input_count, &output_count))
            return (true);
        fcmd = cmd;
    } while (*(cmd++));
    if (shell_cmd && !validate_redirection_args(shell_cmd, fcmd, cmd))
        return (true);
    return (false);
}