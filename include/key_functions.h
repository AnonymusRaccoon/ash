/*
** EPITECH PROJECT, 2020
** ash
** File description:
** bindings
*/

#pragma once

#include "shell.h"

#define CTRL(c) ((c) & 0x1F)

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

int buffer_get_display_pos(buffer_t *buffer);


int self_insert_command(int key, buffer_t *buffer, env_t *env);
int newline_command(int key, buffer_t *buffer, env_t *env);
int eof_command(int key, buffer_t *buffer, env_t *env);
int backward_delete_char_command(int key, buffer_t *buffer, env_t *env);