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

char *add_to_buffer(char *buffer, char *ptr, int nb, env_t *env)
{
    char *new;
    
    if (nb <= 0)
        return (buffer);
    new = strndup(ptr, nb + 1);
    if (!new)
        return (NULL);
    new[nb] = '\0';
    if (env) {
        remove_inhibitors_symbols_n_limit(new, nb);
        new = process_vars(new, env);
        if (!new)
            return (NULL);
    }
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

char *substring(char *string, int position, int length)
{
    char *pointer = malloc(length + 1);
    int i;

    if (pointer == NULL)
       return (NULL);
    for (i = 0; i < length; i++)
        *(pointer + i) = *((string + position - 1) + i);
    *(pointer + i) = '\0';
   return (pointer);
}

void insert_substring(char *dest, char *src, int position)
{
   char *f;
   char *e;
   int length;

   length = strlen(dest);
   f = substring(dest, 1, position - 1);
   e = substring(dest, position, length - position + 1);
   strcpy(dest, "");
   strcat(dest, f);
   free(f);
   strcat(dest, src);
   strcat(dest, e);
   free(e);
}