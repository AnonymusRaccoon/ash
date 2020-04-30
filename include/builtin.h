/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** builtin
*/

#pragma once

#include "shell.h"

typedef struct builtin {
    const char *name;
    int (*run)(char **argv, env_t *env);
} builtin;

int run_builtin(const builtin *cmd, char **argv, \
redirection *inout[2], env_t *env);

int builtin_env(char **argv, env_t *env);
int builtin_setenv(char **argv, env_t *env);
int builtin_unsetenv(char **argv, env_t *env);
int builtin_cd(char **argv, env_t *env);
int builtin_exit(char **argv, env_t *env);
int builtin_history(char **args, env_t *env);

//history
int add_to_history(char *cmd, env_t *env);
int show_history(env_t *env);
int clear_history(env_t *env);
int execute_from_history(char **args, env_t *env);
void remove_duplicate_history(env_t *env);
int execute_command_history(history_t *old, history_t *new,
char **args, env_t *env);