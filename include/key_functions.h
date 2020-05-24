/*
** EPITECH PROJECT, 2020
** ash
** File description:
** bindings
*/

#pragma once

#include "shell.h"

typedef struct key_function
{
    const char *name;
    int (*run)(int key, buffer_t *command_buffer, env_t *env);
} key_function_t;

typedef struct binding
{
    int key;
    int (*func)(int key, buffer_t *command_buffer, env_t *env);
} binding_t;

extern const key_function_t key_functions[];
extern const binding_t emacs_bindings[];

int get_emacs_bindings_size();

int buffer_get_display_pos(buffer_t *buffer);


int self_insert_command(int key, buffer_t *buffer, env_t *env);
int newline_command(int key, buffer_t *buffer, env_t *env);
int eof_command(int key, buffer_t *buffer, env_t *env);

int backward_delete_char_command(int key, buffer_t *buffer, env_t *env);
int delete_char_command(int key, buffer_t *buffer, env_t *env);

int forward_char_command(int key, buffer_t *buffer, env_t *env);
int backward_char_command(int key, buffer_t *buffer, env_t *env);
int beginning_of_line_command(int key, buffer_t *buffer, env_t *env);
int end_of_line_command(int key, buffer_t *buffer, env_t *env);

int up_history_command(int key, buffer_t *buffer, env_t *env);
int down_history_command(int key, buffer_t *buffer, env_t *env);

int quoted_insert_command(int key, buffer_t *buffer, env_t *env);
int clear_screen_command(int key, buffer_t *buffer, env_t *env);
int complete_command(int key, buffer_t *buffer, env_t *env);

int tty_sigintr_command(int key, buffer_t *buffer, env_t *env);