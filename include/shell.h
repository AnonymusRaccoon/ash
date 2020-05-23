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
#include "my_ncurses.h"

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
    int history_index;
    char *saved_buffer;
} buffer_t;

typedef struct alias_s
{
    char *alias;
    char *command;
    struct alias_s *next;
} alias_t;

typedef struct env_s
{
    char **env;
    char **vars;
    history_t *history;
    binding_t *bindings;
    my_window *window;
    alias_t *alias;
} env_t;

void start_shell(env_t *env);
void free_env(env_t *env);
int prompt_run(char *cmd, redirection *inout[2], env_t *env, redirection *red);
void prompt_prepare(buffer_t *buffer, env_t *env);

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

char *get_alias(char *cmd, alias_t *alias);
char *add_separator(char *cmd, int *return_values, int index);
char *replace_alias(char *cmd, alias_t *alias);
char *get_alias_command(char *cmd, alias_t *alias);


#define ERROR 84