/*
** EPITECH PROJECT, 2019
** my_strcmp
** File description:
** task06 day06
*/

static int find_relation(char const *s1, char const *s2, int i)
{
    if (s1[i] > s2[i])
        return (1);
    else if (s1[i] < s2[i])
        return (-1);
    else
        return (0);
}

int my_strcmp(char const *s1, char const *s2)
{
    int i = 0;
    while ((s1[i] != '\0') || (s2[i] != '\0')) {
        if (s1[i] != s2[i]) {
            return (find_relation(s1, s2, i));
        }
        i++;
    }
    return (0);
}
