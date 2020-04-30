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

char **split_commands(char *cmd)
{
    char **array = NULL;
    int len = 1;
    int pos = 0;

    for (int i = 0; cmd[i]; i++) {
        len += (cmd[i] == ';') ? 1 : 0;
        len += (cmd[i] == '&' && cmd[i + 1] == '&') ? 1 : 0;
        len += (cmd[i] == '|' && cmd[i + 1] == '|') ? 1 : 0;
    }
    array = malloc(sizeof(char *) * (len + 1));
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