/*
** EPITECH PROJECT, 2019
** my_put_nbr
** File description:
** task07 day03
*/

void my_putchar(char c);

int my_put_nbr(int nb)
{
    long lnb = nb;

    if (lnb < 0) {
        my_putchar('-');
        lnb = lnb * -1;
    }
    if (lnb >= 10) {
        my_put_nbr(lnb / 10);
        my_put_nbr(lnb % 10);
    }
    else {
        my_putchar(lnb + '0');
    }
    return (0);
}