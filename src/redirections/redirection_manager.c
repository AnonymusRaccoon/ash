/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** redirections
*/


#include "shell.h"
#include "redirections.h"
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdio.h>
#include "utility.h"
#include "builtin.h"

const redirection_map redirections[] = {
    {"|", &get_pipe_fd, &handle_pipe, OUTPUT | PIPE | EX_PIPE},
    {">>", &get_append_output_redirect_fd, NULL, OUTPUT},
    {">", &get_output_redirect_fd, NULL, OUTPUT},
    {"<<", &get_append_input_redirect_fd, &handle_eof_input, INPUT | EX_PIPE},
    {"<", &get_input_redirect_fd, NULL, INPUT},
    {NULL, NULL, NULL, 0}
};

const redirection_map *get_redirection(char *c)
{
    for (int i = 0; redirections[i].key; i++)
        if (!strncmp(redirections[i].key, c, strlen(redirections[i].key)))
            return (&redirections[i]);
    return (NULL);
}

redirection *split_redirections(char *cmd)
{
    int count = 0;
    redirection *cmds;
    const redirection_map *shell_cmd;
    int j = 0;

    for (int i = 0; redirections[i].key; i++)
        count += count_str(cmd, redirections[i].key);
    if (!(cmds = malloc(sizeof(redirection) * (count + 1))))
        return (NULL);
    while (*(cmd++)) {
        shell_cmd = get_redirection(cmd);
        if (!shell_cmd)
            continue;
        *cmd = '\0';
        cmd += strlen(shell_cmd->key);
        redirection_ctr(&cmds[j++], cmd, shell_cmd);
        if (shell_cmd->type & PIPE)
            break;
    }
    cmds[j].type = NULL;
    return (cmds);
}

int run_with_redirections(char *cmd, env_t *env, redirection *input)
{
    redirection *cmds = split_redirections(cmd);
    static redirection *inout[2];

    inout[0] = input;
    inout[1] = NULL;
    if (!cmds || !cmds[0].type)
        return (prompt_run(cmd, inout, env, cmds));
    for (int i = 0; cmds[i].type; i++) {
        if (cmds[i].type->type & INPUT)
            inout[0] = &cmds[i];
        else
            inout[1] = &cmds[i];
        if (cmds[i].type->type & PIPE)
            return (prompt_run(cmd, inout, env, cmds));
    }
    return (prompt_run(cmd, inout, env, cmds));
}

bool command_format_is_invalid(char **cmds, env_t *env, int *return_values)
{
    if (cmds[0] && !cmds[0][count_trailing_spaces(cmds[0])] && !cmds[1])
        return (false);
    for (int i = 0; cmds[i]; i++) {
        if (!cmds[i] || !cmds[i][count_trailing_spaces(cmds[i])]
        || split_is_invalid(cmds, return_values, i)) {
            dprintf(2, "Invalid null command.\n");
            env->vars = my_setenv(env->vars, "?", "1");
            return (true);
        } else if (redirections_are_invalid(cmds[i])) {
            env->env = my_setenv(env->vars, "?", "1");
            return (true);
        }
    }
    return (false);
}

int eval_raw_cmd(char *cmd, env_t *env)
{
    int *return_values = NULL;
    char **cmds =  split_str(cmd, (char *[]){";", "||", "&&", NULL});
    char **const_cmd = cmds;
    int ret = 0;

    return_values = get_return_separator(cmd);
    cmds = remove_leading_entries(cmds);
    if (!cmds || !return_values)
        return (-1);
    if (command_format_is_invalid(cmds, env, return_values))
        return (free(const_cmd), free(return_values), 0);
    for (int i = 0; cmds[i]; i++) {
        if ((return_values[i] == 0 && get_return(my_getenv(env->vars, "?"))) ||
        (return_values[i] == 1 && !get_return(my_getenv(env->vars, "?")))){
            for (; return_values[i + 1] != -1 && cmds[i + 1]; i++);
        } else if (run_with_redirections(cmds[i], env, NULL))
            ret = -1;
    }
    free(const_cmd);
    free(return_values);
    return (ret);
}