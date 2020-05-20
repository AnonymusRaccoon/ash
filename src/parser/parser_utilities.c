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

char *add_to_buffer(char *buffer, char *ptr, int nb)
{
    char *new;
    
    if (nb <= 0)
        return (buffer);
    new = strndup(ptr, nb + 1);
    if (!new)
        return (NULL);
    new[nb] = '\0';
    buffer = strcat_realloc(buffer, new);
    free(new);
    return (buffer);
}