/*
** EPITECH PROJECT, 2019
** my_revstr
** File description:
** task04 day06
*/
void my_putchar(char c);
int my_putstr(char const *str);

static int my_strlen_revstr(char const *str)
{
    int i = 0;
    while (str[i] != '\0') {
        i++;
    }
    return i;
}

char *my_revstr(char *str)
{
    int max = my_strlen_revstr(str);
    int maxcache = (max + 1) / 2;
    char c;
    int i;
    for (i = 0; i < maxcache; i++) {
        c = str[i];
        str[i] = str[max - 1];
        str[max - 1] = c;
        max--;
    }
    return (str);
}
