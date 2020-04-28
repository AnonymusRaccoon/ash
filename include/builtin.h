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
int builtin_which(char **argv, env_t *env);
int builtin_where(char **argv, env_t *env);

//utility
int check_builtins(char *cmd);
char **get_envpath(env_t *env);