/*
** EPITECH PROJECT, 2020
** grt_inhibitor.c
** File description:
** get_inhibitor
*/

#include <shell.h>
#include <unistd.h>

char *get_inhibitor(char *cmd)
{
    bool inhibitor_interpreter = true;

    if (cmd[0] != '\'' && cmd[0] != '\"')
        inhibitor_interpreter = false;
    for (int i = 0; cmd[i]; i++) {
        if (cmd[i] != '\\')
            continue;
        if (cmd[i + 1] == 'n' && inhibitor_interpreter)
            cmd[i + 1] = '\n';
        if (cmd[i + 1] == 'b' && inhibitor_interpreter)
            cmd[i + 1] = '\b';
        if (cmd[i + 1] == 't' && inhibitor_interpreter)
            cmd[i + 1] = '\t';
        if (cmd[i + 1] == 'v' && inhibitor_interpreter)
            cmd[i + 1] = '\v';
        for (int k = i; cmd[k]; k++)
            cmd[k] = cmd[k + 1];
    }
    return (cmd);
}