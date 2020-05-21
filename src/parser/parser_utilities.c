/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** parser_utilities
*/

#include <malloc.h>
#include "parser.h"



char *strcat_realloc(char *dest, char *src)
{
    if (dest) {
        dest = realloc(dest, sizeof(char) * (strlen(dest) + strlen(src) + 1));
        if (!dest)
            return (NULL);
    } else {
        dest = malloc(sizeof(char) * (strlen(src) + 1));
        if (!dest)
            return (NULL);
        dest[0] = '\0';
    }
    strcat(dest, src);
    return (dest);
}

char *add_to_buffer(char *buffer, char *ptr, int nb, bool inhibitors)
{
    char *new;
    
    if (nb <= 0)
        return (buffer);
    new = strndup(ptr, nb + 1);
    if (!new)
        return (NULL);
    new[nb] = '\0';
    if (inhibitors)
        remove_inhibitors_symbols_n_limit(new, nb);
    buffer = strcat_realloc(buffer, new);
    free(new);
    return (buffer);
}

void remove_inhibitors_symbols_n_limit(char *str, int nb)
{
    for (int i = 0; str[i] && i < nb; i++) {
        if (str[i] == '\\') {
            for (int j = i; str[j]; j++) {
                str[j] = str[j + 1];
            }
            i++;
        }
    }
}