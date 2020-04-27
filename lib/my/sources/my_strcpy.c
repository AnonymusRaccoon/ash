/*
** EPITECH PROJECT, 2019
** my_strcpy
** File description:
** task01 day06
*/

char *my_strcpy(char *dest, char const *src)
{
    int i;
    for (i = 0; src[i] != '\0'; i++) {
        dest[i] = src[i];
    }
    if (i == 0) {
        dest[i] = '\0';
    }
    else {
        dest[i] = '\0';
    }
    return (dest);
}
