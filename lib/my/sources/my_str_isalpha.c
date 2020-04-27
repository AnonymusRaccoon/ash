/*
** EPITECH PROJECT, 2019
** my_str_isalpha
** File description:
** task12 day06
*/

static int is_allowed_char_alpha(char const *str, int i)
{
    if ((str[i] >= 'a' && str[i] <= 'z') \
|| (str[i] >= 'A' && str[i] <= 'Z')) {
        return (1);
    }
    else
        return (0);
}

int my_str_isalpha(char const *str)
{
    if (str[0] == '\0')
        return (1);
    for (int i = 0; str[i] != '\0'; i++) {
        if (is_allowed_char_alpha(str, i) == 0) {
            return (0);
        }
    }
    return (1);
}
