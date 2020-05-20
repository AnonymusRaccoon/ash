/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** redirections
*/

#pragma once

#include "shell.h"

typedef struct parser_map {
    char *key;
    int (*parser)(char *, char **);
} parser_map;

char **parse_input(char *cmd);
int parse_quotes(char *ptr, char **data);