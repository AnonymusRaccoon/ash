/*
** EPITECH PROJECT, 2020
** fusion.c
** File description:
** fusion
*/

#include <string.h>
#include <stdlib.h>

char *fusion(char *command, char **args)
{
    char *str = NULL;
    int len = strlen(command) + 1;
    int pos = 0;
    if (!args[1])
        return (command);
    for (int i = 1; args[i]; i++)
        len += strlen(args[i]) + 1;
    str = malloc(sizeof(char) * (len + 1));
    if (!str)
        return (NULL);
    strcpy(str, command);
    pos += strlen(command);
    str[pos++] = ' ';
    for (int i = 1; args[i]; i++) {
        strcpy(str + pos, args[i]);
        pos += strlen(args[i]);
        str[pos++] = ' ';
    }
    str[pos] = 0;
    return (str);
}