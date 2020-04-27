/*
** EPITECH PROJECT, 2019
** task1 day13
** File description:
** none
*/

int my_str_is_alphanum(const char *str)
{
    for (int i = 0; str[i]; i++) {
        if (str[i] >= '0' && str[i] <= '9')
            continue;
        if (str[i] >= 'a' && str[i] <= 'z')
            continue;
        if (str[i] >= 'A' && str[i] <= 'Z')
            continue;
        if (str[i] == '_')
            continue;
        return (0);
    }
    return (1);
}