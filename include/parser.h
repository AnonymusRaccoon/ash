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
    int (*parser)(char *, char **);
} parser_map;

char **parse_input(char *cmd);
int parse_quotes(char *ptr, char **data);

char *strcat_realloc(char *dest, char *src);
char *add_to_buffer(char *buffer, char *ptr, int nb, bool inhibitors);

void remove_inhibitors_symbols_n_limit(char *str, int nb);