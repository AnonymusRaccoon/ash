/*
** EPITECH PROJECT, 2019
** long long int
** File description:
** r
*/

void my_putchar(char c);
int my_strlen(char const *str);
int max_index_of_base(char const *base);
void print(int result, char const *base);

#include <stdio.h>

int my_putnbr_base_long(unsigned long int nbr, char const *base)
{
    if (nbr == 0) {
        return (0);
    }

    int divider = my_strlen(base);

    my_putnbr_base_long(nbr / divider, base);
    print(nbr % divider, base);
    return (0);
}