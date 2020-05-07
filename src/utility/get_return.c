/*
** EPITECH PROJECT, 2020
** ash
** File description:
** get_return
*/

#include <stdlib.h>

int get_return(char *ret)
{
    if (!ret)
        return (0);
    return (atoi(ret));
}