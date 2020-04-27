/*
** EPITECH PROJECT, 2019
** Str is alpha
** File description:
** Duplicate of the string.h (I think)
*/

#include <stdbool.h>

bool is_alpha(char c)
{
    if (c >= 'a' && c <= 'z')
        return (true);
    if (c >= 'A' && c <= 'Z')
        return (true);
    return (false);
}

bool is_num(char c)
{
    if (c >= '0' && c <= '9')
        return (true);
    return (false);
}

bool envvar_is_valid(const char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (!is_alpha(str[i]) && !is_num(str[i]) && str[i] != '_')
            return (false);
    }
    return (true);
}
