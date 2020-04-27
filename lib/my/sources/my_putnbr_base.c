/*
** EPITECH PROJECT, 2019
** my_putnbr_base
** File description:
** task18 day6
*/

void my_putchar(char c);
int my_strlen(char const *str);

#include <stdio.h>

int max_index_of_base(char const *base)
{
    int inc = 0;

    for (int i = 0; base[i] != '\0'; i++) {
        inc++;
    }
    return (inc);
}

void print(int result, char const *base)
{
    my_putchar(base[result]);
}

int my_putnbr_base(int nbr, char const *base)
{
    if (nbr < 0) {
        my_putchar('-');
        nbr = nbr * -1;
    }

    if (nbr == 0) {
        return (0);
    }

    int divider = my_strlen(base);

    my_putnbr_base(nbr / divider, base);
    print(nbr % divider, base);
    return (0);
}