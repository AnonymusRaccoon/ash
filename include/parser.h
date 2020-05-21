/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** redirections
*/

#pragma once

#include "shell.h"
#include <stddef.h>
#include <string.h>

typedef struct parser_map {
    char key;
    int (*parser)(char *, char **, env_t *);
} parser_map;

char **parse_input(char *cmd, env_t *env);

int parse_quotes(char *ptr, char **data, env_t *env);
int parse_double_quotes(char *ptr, char **data, env_t *env);

char *strcat_realloc(char *dest, char *src);
char *add_to_buffer(char *buffer, char *ptr, int nb, bool inhibitors);
char *get_var_value(char *var, env_t *env);

void insert_substring(char *dest, char *src, int position);

char *process_vars(char *cmd, env_t *env);
void rm_n_char(char *ptr, int n);

void remove_inhibitors_symbols_n_limit(char *str, int nb);