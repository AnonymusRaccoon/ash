/*
** EPITECH PROJECT, 2019
** my_compute_square_root
** File description:
** task05 day05
*/

int my_compute_square_root(int nb)
{
    if (nb <= 0)
        return (0);
    if (nb == 1)
        return (1);

    int power = 1;
    int rpower = 1;

    while (rpower < nb) {
        rpower = power*power;
        power++;
    }

    if (rpower == nb) {
        return (power - 1);
    }
    else {
        return (0);
    }
}
