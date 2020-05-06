/*
** EPITECH PROJECT, 2020
** ash
** File description:
** bindings
*/

#include "shell.h"

#pragma once

typedef struct key_function
{
    const char *name;
    int (*run)(int key, buffer_t *command_buffer, env_t *env);
} key_function_t;

extern const key_function_t key_functions[];

int self_insert_command(int key, buffer_t *command_buffer, env_t *env);