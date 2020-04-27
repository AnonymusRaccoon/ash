/*
** EPITECH PROJECT, 2019
** get_my_digit
** File description:
** dedefee
*/

int my_get_digit(int nb)
{
    int count = 1;

    for (int i = 10; nb / i != 0; i *= 10)
        count++;
    return (count);
}
