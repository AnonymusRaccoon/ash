/*
** EPITECH PROJECT, 2020
** ash
** File description:
** utility
*/

#pragma once

#include <stdbool.h>
#include "shell.h"

char *catpath(char *p1, char *p2);
char **to_array(char *str);
char *tostr(int n);
bool is_alpha(char c);
bool is_num(char c);
bool envvar_is_valid(const char *str);
int count_str(char *str, char *delim);
char **split_str(char *str, char **delims);
char *same_var(char *str, const char *to_find);
void destroy_str_arr(char **arr);
char *fusion(char *command, char **args);
int *get_return_separator(char *cmd);
int split_is_invalid(char **cmds, int *return_values, int i);
int count_char(const char *str, char c);
int ncount_char(const char *str, int end, char c);
int get_max_eof(char *ignoreeof);
int skip_eof(buffer_t *buffer, env_t *env);
int count_trailing_spaces(char *cmd);
char **remove_leading_entries(char **cmds);

#define MAX(x, y) ((x) < (y) ? (y) : (x))
