/*
** EPITECH PROJECT, 2020
** quotes
** File description:
** quotes
*/

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

bool matched_quotes(char *cmd)
{
    int nb_simple = 0;
    int nb_double = 0;

    for (int i = 0; cmd[i]; i++) {
        if (cmd[i] == '\\') {
            i++;
            continue;
        }
        if (cmd[i] == '\'')
            nb_simple++;
        if (cmd[i] == '\"')
            nb_double++;
    }
    if (nb_double % 2 == 1)
        printf("Unmatched '\"'.\n");
    else if (nb_simple % 2 == 1)
        printf("Unmatched '\''.\n");
    if (nb_double % 2 == 1 || nb_simple % 2 == 1)
        return (false);
    return (true);
}

char **remove_quotes(char **argv)
{
    int len = 0;
    for (int i = 0; argv[i]; i++) {
        len = strlen(argv[i]);
        if ((argv[i][0] == '\"' && argv[i][len - 1] == '\"')
        || (argv[i][0] == '\'' && argv[i][len - 1] == '\'')) {
            argv[i][len - 1] = 0;
            argv[i]++;
        }
    }
    return (argv);
}