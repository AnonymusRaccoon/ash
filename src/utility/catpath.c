/*
** EPITECH PROJECT, 2019
** PSU_my_ls_2019
** File description:
** catpath
*/

#include "my.h"
#include <stdlib.h>

char *catpath(char *p1, char *p2)
{
    char *ret = malloc((my_strlen(p1) + my_strlen(p2) + 2) * sizeof(char));

    my_strcpy(ret, p1);
    my_strcat(ret, "/");
    my_strcat(ret, p2);
    return (ret);
}