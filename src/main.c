/*
** EPITECH PROJECT, 2020
** PSU_minishell1_2019
** File description:
** main
*/

#include "shell.h"
#include "key_functions.h"
#include <stdlib.h>
#include <malloc.h>
#include <stddef.h>
#include <string.h>

env_t *create_env(char **env)
{
    env_t *envt = malloc(sizeof(*envt));
    char **envcp = malloc(sizeof(char *) * (env_get_length(env) + 1));

    if (!env || !envcp)
        return (NULL);
    for (int i = 0; env[i]; i++)
        envcp[i] = strdup(env[i]);
    envcp[env_get_length(env)] = NULL;
    envt->env = envcp;
    envt->vars = NULL;
    envt->history = NULL;
    envt->bindings = &emacs_bindings;
    envt->window = NULL;
    return (envt);
}

int main(int argc, char **argv, char **env)
{
    env_t *envt = create_env(env);
    int ret;

    if (!envt)
        return (ERROR);
    start_shell(envt);
    (void)argc;
    (void)argv;
    ret = get_return(my_getenv(envt->vars, "?"));
    free_env(envt);
    return (ret);
}