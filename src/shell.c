/*
** EPITECH PROJECT, 2020
** PSU_minishell1_2019
** File description:
** shell
*/

#include "shell.h"
#include "builtin.h"
#include "key_functions.h"
#include <stdbool.h>
#include <stdio.h>
#include <malloc.h>
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

int process_key(int key, buffer_t *buffer, env_t *env)
{
    for (int i = 0; env->bindings[i].func; i++)
        if (key == env->bindings[i].key)
            return (env->bindings[i].func(key, buffer, env));
    return (self_insert_command(key, buffer, env));
}

void start_shell(env_t *env)
{
    WINDOW *window = initscr();
    int key;
    buffer_t buffer = {.size = 0, .buffer = NULL, .pos = 0};

    noecho();
    keypad(window, true);
    cbreak();
    prompt_prepare(env);
    do {
        printf("%s \n", buffer.buffer);
        key = getch();
        if (key == ERR)
            break;
    } while (process_key(key, &buffer, env) >= 0);
    delwin(window);
    nocbreak();
    endwin();
}