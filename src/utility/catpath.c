/*
** EPITECH PROJECT, 2019
** PSU_ls_2019
** File description:
** catpath
*/


#include <stdlib.h>
#include <string.h>

char *catpath(char *p1, char *p2)
{
    char *ret = malloc((strlen(p1) + strlen(p2) + 2) * sizeof(char));

    strcpy(ret, p1);
    strcat(ret, "/");
    strcat(ret, p2);
    return (ret);
}