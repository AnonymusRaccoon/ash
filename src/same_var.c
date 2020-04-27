/*
** EPITECH PROJECT, 2020
** PSU_minishell1_2019
** File description:
** same_var
*/

#include <stddef.h>

char *same_var(char *str, const char *to_find)
{
    int i;
    int search_index = 0;

    for (i = 0; str[i] != '\0'; i++) {
        if (to_find[search_index] == '\0') {
            if (str[i] == '=')
                return (str + i - search_index);
            return (NULL);
        }
        if (str[i] == to_find[search_index])
            search_index++;
        else if (str[i] == to_find[0])
            search_index = 1;
        else
            search_index = 0;
    }
    if (to_find[search_index] == '\0')
        return (str + i - search_index);
    return (NULL);
}