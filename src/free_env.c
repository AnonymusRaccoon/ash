/*
** EPITECH PROJECT, 2020
** PSU_minishell1_2019
** File description:
** free_env
*/

#include "shell.h"
#include <malloc.h>

void free_env(env_t *env)
{
    if (env->env) {
        for (int i = 0; env->env[i]; i++)
            free(env->env[i]);
        free(env->env);
    }
    if (env->vars) {
        for (int i = 0; env->vars[i]; i++)
            free(env->vars[i]);
        free(env->vars);
    }
    free(env);
}