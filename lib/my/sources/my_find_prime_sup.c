/*
** EPITECH PROJECT, 2019
** my_find_prime_sup
** File description:
** task07 day05
*/
static int my_is_prime_spec(int nb);

int my_find_prime_sup(int nb)
{
    if (nb <= 1)
        return (2);

    while (my_is_prime_spec(nb) == 0) {
        nb++;
    }
    return (nb);
}

static int my_is_prime_spec(int nb)
{
    int s;
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
