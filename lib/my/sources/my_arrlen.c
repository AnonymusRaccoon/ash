/*
** EPITECH PROJECT, 2019
** task1 day13
** File description:
** none
*/

int my_arrlen(void **arr)
{
    int i = 0;

    while (arr[i])
        i++;
    return (i);
}