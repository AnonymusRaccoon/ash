/*
** EPITECH PROJECT, 2020
** PSU_minishell1_2019
** File description:
** vars
*/

#include <malloc.h>
#include <stddef.h>
#include <string.h>
#include "utility.h"


char *my_getenv(char **env, char *name)
{
    if (!env)
        return (NULL);
    for (int i = 0; env[i]; i++) {
        if (same_var(env[i], name) == env[i])
            return (env[i] + strlen(name) + 1);
    }
    return (NULL);
}

char *create_envvar(char *name, char *value)
{
    int len = strlen(name) + (value ? strlen(value) : 0);
    char *var = malloc(sizeof(char) * (len + 2));

    if (!var)
        return (NULL);
    strcpy(var, name);
    strcat(var, "=");
    if (value)
        strcat(var, value);
    return (var);
}

char **my_setenv(char **env, char *name, char *value)
{
    size_t old = sizeof(char *);
    int i;

    for (i = 0; env && env[i]; i++) {
        if (same_var(env[i], name) == env[i]) {
            free(env[i]);
            env[i] = create_envvar(name, value);
            return (env);
        }
    }
    for (i = 0; env && env[i]; i++)
        old += sizeof(char *);
    env = realloc(env, old + sizeof(char *));
    if (!env)
        return (NULL);
    env[i] = create_envvar(name, value);
    env[i + 1] = NULL;
    return (env);
}

int env_get_length(char **env)
{
    int i = 0;

    if (!env)
        return (0);
    while (env[i])
        i++;
    return (i);
}

char **my_unsetenv(char **env, char *name)
{
    int max = env_get_length(env);

    for (int i = 0; env[i]; i++) {
        if (same_var(env[i], name) == env[i]) {
            free(env[i]);
            env[i] = env[max - 1];
            env[max - 1] = NULL;
        }
    }
    return (env);
}
