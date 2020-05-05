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
#include "builtin.h"
#include <string.h>
#include <errno.h>
#include <ncurses.h>

void test()
{
    // char *cmd = NULL;
    // size_t read = 0;
    // char *p;
    // bool should_close = false;

    // while (!should_close) {
    //     if (cmd) {
    //         p = strchr(cmd, '\n');
    //         if (p)
    //             *p = '\0';
    //         add_to_history(cmd, env);
    //         if (eval_raw_cmd(cmd, env) < 0)
    //             should_close = true;
    //     }
    //     if (!should_close) {
         //    prompt_prepare(env);
    //         should_close = getline(&cmd, &read, stdin) < 0;
    //     }
    // }
    // if (cmd)
    //     free(cmd);
}

int process_key(int key, char *buffer, env_t *env)
{
    for (int i = 0; env->bindings[i].func; i++)
        if (key == env->bindings[i].key)
            return (env->bindings[i].func->run(key, buffer, env));
    return (0);
}

void start_shell(env_t *env)
{
    WINDOW *window = initscr();
    int key;
    char *buffer = calloc(100, sizeof(char));

    noecho();
    prompt_prepare(env);
    do {
        key = getch();
        if (key == ERR)
            break;
    } while (process_key(key, buffer, env) > 0);
    delwin(window);
    endwin();
}