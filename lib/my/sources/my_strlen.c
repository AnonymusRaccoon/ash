/*
** EPITECH PROJECT, 2019
** my_strlen
** File description:
** task03 day04
*/

int my_strlen(char const *str)
{
    int i = 0;
    while (str[i] != '\0') {
        i++;
    }
    return (i);
}