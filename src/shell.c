/*
** EPITECH PROJECT, 2020
** PSU_minishell1_2019
** File description:
** shell
*/

#include <stdbool.h>
#include <stdio.h>
#include <malloc.h>
#include "shell.h"
#include "my.h"

#include <errno.h>

void start_shell(env_t *env)
{
    char *cmd = NULL;
    size_t read = 0;
    char *p;
    bool should_close = false;

    while (!should_close) {
        if (cmd) {
            p = my_strchr(cmd, '\n');
            if (p)
                *p = '\0';
            if (eval_raw_cmd(cmd, env) < 0)
                should_close = true;
        }
        if (!should_close) {
            prompt_prepare(env);
            should_close = getline(&cmd, &read, stdin) < 0;
        }
    }
    if (cmd)
        free(cmd);
}