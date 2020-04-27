/*
** EPITECH PROJECT, 2020
** PSU_minishell1_2019
** File description:
** main
*/

#include "shell.h"
#include "my.h"
#include <malloc.h>
#include <stddef.h>

int get_return(char *ret)
{
    if (!ret)
        return (0);
    if (!my_str_isnum(ret))
        return (0);
    return (my_getnbr(ret));
}

int main(int argc, char **argv, char **env)
{
    env_t *envt = malloc(sizeof(*envt));
    char **envcp = malloc(sizeof(char *) * (env_get_length(env) + 1));
    int ret;

    if (!env || !envcp)
        return (84);
    for (int i = 0; env[i]; i++)
        envcp[i] = my_strdup(env[i]);
    envcp[env_get_length(env)] = NULL;
    envt->env = envcp;
    envt->vars = NULL;
    start_shell(envt);
    ret = get_return(my_getenv(envt->vars, "?"));
    (void)argc;
    (void)argv;
    free_env(envt);
    return (ret);
}