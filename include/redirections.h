/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** redirections
*/

typedef struct redirection redirection;

#pragma once

#include "shell.h"

typedef enum redirection_type {
    INPUT = 1 << 0,
    OUTPUT = 1 << 1,
    PIPE = 1 << 2,
    EX_PIPE = 1 << 3,
    PTY = 1 << 4
} redirection_type;


typedef struct redirection_map {
    char *key;
    int (*get_fd)(redirection *);
    void (*run_cmd)(redirection *, env_t *env);
    redirection_type type;
} redirection_map;

struct redirection {
    const redirection_map *type;
    char *arg;
    int fd;
    int extra_data;
};

const redirection_map *get_redirection(char *c);
void redirection_ctr(redirection *r, char *cmd, const redirection_map *t);

int get_input_redirect_fd(redirection *input);
int get_append_input_redirect_fd(redirection *input);
int get_output_redirect_fd(redirection *output);
int get_append_output_redirect_fd(redirection *output);
int get_pipe_fd(redirection *output);

void handle_pipe(redirection *command, env_t *env);
void handle_eof_input(redirection *command, env_t *env);

bool redirections_are_invalid(char *cmd);
bool fd_is_used(int fd, redirection *inout);

bool handle_redirections(redirection *inout[2], env_t *env, bool builtin);
bool handle_parent_inout(redirection *inout[2], env_t *env, bool builtin);


struct redirection *new_ncurses_pty();
int pyt_get_fd(redirection *pty);
void pty_get_output(redirection *pty, env_t *env);