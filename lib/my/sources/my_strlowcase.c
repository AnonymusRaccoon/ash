/*
** EPITECH PROJECT, 2019
** my_strlowcase
** File description:
** task09 day06
*/

char *my_strlowcase(char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z'){
            str[i] = str[i] + 'a' - 'A';
        }
    }
    return (str);
}
