/*
** EPITECH PROJECT, 2019
** my put str e
** File description:
** fe
*/

#include "../includes/my.h"

void put_zero(char c)
{
    my_putchar('0');
    if (c < 8)
        my_putchar('0');
}

void my_putstr_e(char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 32 && str[i] < 127)
            my_putchar(str[i]);
        else {
            my_putchar('\\');
            put_zero(str[i]);
            my_putnbr_base(str[i], "01234567");
        }
    }
}