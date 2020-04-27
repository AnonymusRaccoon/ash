/*
** EPITECH PROJECT, 2019
** my_swap
** File description:
** task01 day04
*/

void my_putchar(char c);

void my_swap(int *a, int *b)
{
    int cache;

    cache = *a;
    *a = *b;
    *b = cache;
}