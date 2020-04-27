/*
** EPITECH PROJECT, 2019
** my_strdup
** File description:
** task01 day08
*/

#include <stdlib.h>

int my_strlen(char const *str);

char *my_strdup(char const *str)
{
    int i = 0;
    int size = my_strlen(str);
    char *newstr = malloc(sizeof(char) * (size + 1));
    for (i = 0; str[i] != '\0'; i++) {
        newstr[i] = str[i];
    }
    newstr[i] = '\0';
    return (newstr);
}
