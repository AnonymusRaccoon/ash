/*
** EPITECH PROJECT, 2019
** my_str_islower
** File description:
** task14 day06
*/

static int is_allowed_char_lower(char const *str, int i)
{
    if ((str[i] >= 'a' && str[i] <= 'z')) {
        return (1);
    }
    else
        return (0);
}

int my_str_islower(char const *str)
{
    if (str[0] == '\0')
        return (1);
    for (int i = 0; str[i] != '\0'; i++) {
        if (is_allowed_char_lower(str, i) == 0) {
            return (0);
        }
    }
    return (1);
}
