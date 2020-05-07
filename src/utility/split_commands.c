/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** split_commands
*/

#include <malloc.h>
#include <stddef.h>
#include <string.h>

int get_command_len(char *str)
{
    int len = 0;

    for (int i = 0; str[i]; i++) {
        if (str[i] == ';' || (str[i] == '&' && str[i + 1] == '&')
            || (str[i] == '|' && str[i + 1] == '|'))
            break;
        len++;
    }
    return (len);
}

int get_nb_commands(char *cmd)
{
    int len = 1;
    for (int i = 0; cmd[i]; i++) {
        len += (cmd[i] == ';') ? 1 : 0;
        len += (cmd[i] == '&' && cmd[i + 1] == '&') ? 1 : 0;
        len += (cmd[i] == '|' && cmd[i + 1] == '|') ? 1 : 0;
    }
    return (len);
}

int *get_return_separator(char *cmd)
{
    int len = get_nb_commands(cmd);
    int *array = malloc(sizeof(int) * (len + 1));
    int pos = 1;

    if (!array)
        return (NULL);
    array[0] = -1;
    array[len] = -2;
    for (int i = 0; cmd[i + 1]; i++) {
        if (cmd[i] == ';')
            array[pos] = -1;
        if (cmd[i] == '&' && cmd[i + 1] == '&')
            array[pos] = 0;
        if (cmd[i] == '|' && cmd[i + 1] == '|')
            array[pos] = 1;
        if ((cmd[i] == '|' && cmd[i + 1] == '|') || (cmd[i] == '&'
            && cmd[i + 1] == '&') || (cmd[i] == ';'))
            pos++;
    }
    return (array);
}

char **split_commands(char *cmd)
{
    int len = get_nb_commands(cmd);
    char **array = malloc(sizeof(char *) * (len + 1));
    int pos = 0;

    array[len] = NULL;
    for (int i = 0; i < len; i++) {
        for (; *cmd && (*cmd == ' ' || *cmd == '\t'); cmd++);
        pos = get_command_len(cmd);
        array[i] = malloc(sizeof(char) * (pos + 1));
        strncpy(array[i], cmd, pos);
        array[i][pos] = 0;
        cmd += pos;
        if (*cmd == ';')
            cmd++;
        else if ((*cmd == '|') || (*cmd == '&'))
            cmd += 2;
    }
    return (array);
}

int split_is_invalid(char **cmds, int *return_values, int i)
{
    if (return_values[i] != 0 && return_values[i] != 1)
        return (0);
    if (i != 0) {
        if (return_values[i] == 1 && !strlen(cmds[i - 1]))
            return (1);
        if (return_values[i] == 0 && !strlen(cmds[i]) && !strlen(cmds[i - 1]))
            return (0);
        if (return_values[i] == 0 && !strlen(cmds[i]))
            return (1);
    }
    if (return_values[i] != -1 && !strlen(cmds[i]))
        return (1);
    return (0);
}