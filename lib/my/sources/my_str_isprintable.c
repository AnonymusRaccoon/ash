/*
** EPITECH PROJECT, 2019
** my_str_isprintable
** File description:
** task16 day06
*/

static int is_allowed_char_printable(char const *str, int i)
{
    if (str[i] >= ' ' && str[i] != 127) {
        return (1);
    }
    else
        return (0);
}

int my_str_isprintable(char const *str)
{
    if (str[0] == '\0')
        return (1);
    for (int i = 0; str[i] != '\0'; i++) {
        if (is_allowed_char_printable(str, i) == 0) {
            return (0);
        }
    }
    return (1);
}
