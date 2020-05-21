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
int builtin_source(char **argv, env_t *env);
int builtin_history(char **args, env_t *env);
int builtin_alias(char **args, env_t *env);
int builtin_unalias(char **args, env_t *env);
//utility
bool find_path_in_builtins(char *cmd);
char **get_envpath(env_t *env);
char *check_executable(char *cmd, char *folder);
char **get_paths_from_envpath(char *cmd, char **envpath);
char **get_envpath(env_t *env);
//history
int add_to_history(char *cmd, env_t *env);
int show_history(env_t *env);
int clear_history(env_t *env);
int execute_from_history(char **args, env_t *env);
void remove_duplicate_history(env_t *env);
int execute_command_history(history_t *old, history_t *new,
char **args, env_t *env);
//source
void init_source_args(char **argv, int len_argv, env_t *env);
void reset_source_args(int len_argv, env_t *env);
//alias
int add_alias(alias_t **list, char *alias, char **command);
char *concatenate(char **command);
void print_aliases(alias_t *list);
int add_alias_to_list(alias_t **list, alias_t *elem, char *alias);

//unalias
void remove_alias(char *alias, alias_t **list);