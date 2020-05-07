/*
** EPITECH PROJECT, 2020
** PSU_minishell1_2019
** File description:
** shell
*/

typedef struct redirection redirection;
typedef struct env_s env_t;
typedef struct binding binding_t;
#pragma once

#define SHELL_NAME "42sh"

#include <stdbool.h>
#include <ncurses.h>

typedef struct history_s
{
    int index;
    char *command;
    int hour;
    int minute;
    int print;
    struct history_s *next;
} history_t;

typedef struct buffer
{
    char *buffer;
    int size;
    int pos;
    int startx;
} buffer_t;

typedef struct env_s
{
    char **env;
    char **vars;
    history_t *history;
    binding_t *bindings;
    WINDOW *window;
} env_t;

void start_shell(env_t *env);
void free_env(env_t *env);
int prompt_run(char *cmd, redirection *inout[2], env_t *env);
void prompt_prepare(buffer_t *buffer, env_t *env);

int eval_raw_cmd(char *cmd, env_t *env);
int run_with_redirections(char *cmd, env_t *env, redirection *input);
void run_cmd(char **argv, redirection *inout[2], env_t *env);
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

#define INVALID_ENV_VAR \
"setenv: Variable name must contain alphanumeric characters.\n"

#define ERROR 84