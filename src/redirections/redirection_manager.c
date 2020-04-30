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
        return (prompt_run(cmd, inout, env));
    for (int i = 0; cmds[i].type; i++) {
        if (cmds[i].type->type & INPUT)
            inout[0] = &cmds[i];
        else
            inout[1] = &cmds[i];
        if (cmds[i].type->type & PIPE)
            return (prompt_run(cmd, inout, env));
    }
    return (prompt_run(cmd, inout, env));
}

int *get_return_separator(char *cmd)
{
    int *array = NULL;
    int len = 1;
    int pos = 1;

    for (int i = 0; cmd[i + 1]; i++) {
        len += (cmd[i] == ';') ? 1 : 0;
        len += (cmd[i] == '&' && cmd[i + 1] == '&') ? 1 : 0;
        len += (cmd[i] == '|' && cmd[i + 1] == '|') ? 1 : 0;
    }
    array = malloc(sizeof(int) * len);
    if (!array)
        return (NULL);
    array[0] = -1;
    for (int i = 0; cmd[i + 1]; i++) {
        if (cmd[i] == ';')
            array[pos] = -1;
        if (cmd[i] == '&' && cmd[i + 1] == '&')
            array[pos] = 0;
        if (cmd[i] == '|' && cmd[i + 1] == '|')
            array[pos] = 1;
        if ((cmd[i] == '|' && cmd[i + 1] == '|') || (cmd[i] == '&'
            && cmd[i + 1] == '&') || (cmd[i] == ';'))
            pos++;
    }
    return (array);
}

int eval_raw_cmd(char *cmd, env_t *env)
{
    int *return_values = get_return_separator(cmd);
    char **cmds = split_commands(cmd);
    int ret = 0;

    if (!cmds)
        return (-1);
    for (int i = 0; cmds[i]; i++) {
        if (redirections_are_invalid(cmds[i])) {
            my_setenv(env->vars, "?", "1");
            return (0);
        }
    }
    for (int i = 0; cmds[i]; i++) {
        if (return_values[i] == 0 && get_return(my_getenv(env->vars, "?")))
            break;
        if (return_values[i] == 1 && !get_return(my_getenv(env->vars, "?")))
            break;
        if (run_with_redirections(cmds[i], env, NULL))
            ret = -1;
    }
    return (ret);
}