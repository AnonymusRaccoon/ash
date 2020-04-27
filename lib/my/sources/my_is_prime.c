/*
** EPITECH PROJECT, 2019
** my_is_prime
** File description:
** task06 day05
*/

int my_is_prime(int nb)
{
    int s = 0;

    if (nb < 2)
        return (0);
    if (nb == 2)
        return (1);
    for (int i = 0; i * i <= nb; i++) {
        s = i;
    }
    for (int j = 2; j < s + 1; j++) {
        if (nb % j == 0)
            return (0);
    }
    return (1);
}
