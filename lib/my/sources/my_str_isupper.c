/*
** EPITECH PROJECT, 2019
** my_str_isupper
** File description:
** task15 day06
*/

static int is_allowed_char_upper(char const *str, int i)
{
    if ((str[i] >= 'A' && str[i] <= 'Z')) {
        return (1);
    }
    else
        return (0);
}

int my_str_isupper(char const *str)
{
    if (str[0] == '\0')
        return (1);
    for (int i = 0; str[i] != '\0'; i++) {
        if (is_allowed_char_upper(str, i) == 0) {
            return (0);
        }
    }
    return (1);
}
