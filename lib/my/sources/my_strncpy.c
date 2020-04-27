/*
** EPITECH PROJECT, 2019
** my_strncpy
** File description:
** task02 day06
*/

char *my_strncpy(char *dest, char const *src, int n)
{
    int mem;
    int i;

    for (int k = 0; src[k] != '\0'; k++)
        mem = k;
    if (n > mem)
        n = mem;
    for (i = 0; i <= n; i++) {
        dest[i] = src[i];
        if (src[n] == '\0' && i == n)
            dest[n] = '\0';
    }
    return (dest);
}
