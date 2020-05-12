/*
** EPITECH PROJECT, 2020
** PSU_minishell1_2019
** File description:
** shell
*/

typedef struct redirection redirection;
#pragma once

#include <stdbool.h>

typedef struct history_s
{
    int index;
    char *command;
    int hour;
    int minute;
    int print;
    struct history_s *next;
} history_t;

typedef struct alias_s
{
    char print;
    char *alias;
    char *command;
    struct alias_s *next;
} alias_t;

typedef struct env_s
{
    char **env;
    char **vars;
    history_t *history;
    alias_t *alias;
} env_t;

void start_shell(env_t *env);
void free_env(env_t *env);
int prompt_run(char *cmd, redirection *inout[2], env_t *env);
void prompt_prepare(env_t *env);

int eval_raw_cmd(char *cmd, env_t *env);
int run_with_redirections(char *cmd, env_t *env, redirection *input);
void run_cmd(char **argv, redirection *inout[2], env_t *env);
char *eval(char *cmd, char **argv, env_t *env);
char *find_binary(char *cmd, char *folder);
void handle_signal(int status, env_t *env);
char **get_argv(char *cmd);
int get_argc(char **argv);
void exec_error(char *path, char *cmd);

int get_return(char *ret);
int env_get_length(char **env);
char *my_getenv(char **env, char *name);
char **my_setenv(char **env, char *name, char *value);
char **my_unsetenv(char **env, char *name);
bool envvar_is_valid(const char *str);

char **globbing(char **argv);

#define INVALID_ENV_VAR \
"setenv: Variable name must contain alphanumeric characters.\n"

char **get_alias(char **argv, env_t *env);


#define ERROR 84