/*
** EPITECH PROJECT, 2019
** Convering Between bases
** File description:
** Moldavie-Land
*/

#include <stdlib.h>

static void put_digit(int n, const char *base, char *ret, int i)
{
    int base_length = 10;

    if (n > base_length - 1)
        put_digit(n / base_length, base, ret, i - 1);
    ret[i] = base[n % base_length];
}

char *putnbr_in(int nbr, const char *base, char *ret, int ret_length)
{
    int base_length = 10;
    int i = ret_length;

    if (base_length < 2) {
        ret = "0";
        return (ret);
    }
    if (nbr < 0) {
        nbr *= -1;
        ret[0] = '-';
    } else {
        i--;
        ret[i] = '\0';
    }
    put_digit(nbr, base, ret, i);
    return (ret);
}

int get_new_size(int n)
{
    int base_size = 10;
    int i = 1;

    while (n >= base_size) {
        n /= base_size;
        i++;
    }
    return (i);
}

char *tostr(int n)
{
    const char *base = "0123456789";
    int count = get_new_size(n);
    char *ret = malloc(sizeof(char) * (count + 1));

    putnbr_in(n, base, ret, count);
    ret[count] = '\0';
    return (ret);
}
