/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** redirections
*/

#include "parser.h"

static void *my_global_bank(char *cmd, bool get_inc, int add_nb)
{
    static char **ret = NULL;
    static int inc_ret = 0;

    if (cmd) {
        ret = malloc(sizeof(char *) * (strlen(cmd) + 1));
        return (ret);
    }
    inc_ret += add_nb;
    if (get_inc || add_nb != 0)
        return ((void *)&inc_ret);
    return (NULL);
}

char **get_ret(char *cmd)
{
    return ((char **)my_global_bank(cmd, false, 0));
}

char **set_ret(char *cmd)
{
    return ((char **)my_global_bank(cmd, false, 0));
}

int get_inc_ret(void)
{
    return (*(int *)(my_global_bank(NULL, true, 0)));
}

void add_inc_ret(int nb)
{
    return (*(int *)(my_global_bank(NULL, true, nb)));
}