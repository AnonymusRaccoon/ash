/*
** EPITECH PROJECT, 2020
** ash
** File description:
** second part of the source function
*/

#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int count_char_in_str(char *str, char c)
{
    int res = 0;

    for (int i = 0; str[i]; i++)
        if (str[i] == c)
            res++;
    return (res);
}

static char *get_str_arg(int arg_index, char **argv)
{
    if (arg_index == 0)
        return ("42sh");
    return (argv[arg_index + 1]);
}

static int get_max_args_len(char **argv)
{
    int max_len = 4;
    int len = 0;

    for (int i = 2; argv[i]; i++) {
        len = strlen(argv[i]);
        if (len > max_len)
            max_len = len;
    }
    return (max_len);
}

void fill_parsed_str(char *result, char *cmd, char **argv, int len_argv)
{
    int counter = 0;
    int argv_index = 0;
    char *str_arg = NULL;

    for (int i = 0; cmd[i]; i++) {
        if (cmd[i] == '$') {
            if (!cmd[i + 1])
                break;
            argv_index = atoi(&cmd[i + 1]);
            if (argv_index <= len_argv - 2 && isdigit(cmd[i + 1])) {
                str_arg = get_str_arg(argv_index, argv);
                for (int j = 0; str_arg[j]; j++)
                    result[counter++] = str_arg[j];
            }
            i++;
        }
        else
            result[counter++] = cmd[i];
    }
    result[counter] = '\0';
}

char *parse_source_cmd(char *cmd, char **argv, int len_argv)
{
    char *result = NULL;
    int max_arg_len = get_max_args_len(argv);
    int max_parsed_str_len = strlen(cmd) +
                            (max_arg_len * count_char_in_str(cmd, '$'));

    result = malloc(sizeof(char) * (max_parsed_str_len + 1));
    if (!result)
        return (NULL);
    fill_parsed_str(result, cmd, argv, len_argv);
    return (result);
}