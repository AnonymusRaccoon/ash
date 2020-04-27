/*
** EPITECH PROJECT, 2019
** my_str_isnum
** File description:
** task13 day06
*/

int my_str_isnum(char const *str)
{
    if (str[0] == '\0')
        return (1);
    for (int i = 0; str[i] != '\0' && str[i] != '\n'; i++) {
        if (str[0] == '-' && i == 0)
            continue;
        if ((str[i] >= '0' && str[i] <= '9'))
            continue;
        return (0);
    }
    return (1);
}
