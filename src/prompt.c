/*
** EPITECH PROJECT, 2020
** PSU_minishell1_2019
** File description:
** prompt
*/


#include "my.h"
#include "shell.h"
#include "builtin.h"
#include "redirections.h"
#include <unistd.h>
#include <malloc.h>

const builtin builtins[] = {
    {"env", &builtin_env},
    {"setenv", &builtin_setenv},
    {"unsetenv", &builtin_unsetenv},
    {"exit", &builtin_exit},
    {"cd", &builtin_cd},
    {NULL, NULL}
};

int prompt_run(char *cmd, redirection *inout[2], env_t *env)
{
    char **argv = get_argv(cmd);

    if (!argv) {
        perror("mysh");
        return (-1);
    }
    if (!argv[0])
        return (0);
    for (int i = 0; builtins[i].name; i++)
        if (!my_strcmp(argv[0], builtins[i].name))
            return (run_builtin(&builtins[i], argv, inout, env));
    run_cmd(argv, inout, env);
    free(argv);
    return (0);
}

void prompt_prepare(env_t *env)
{
    char *prompt = my_getenv(env->vars, "PS1");

    if (isatty(0)) {
        if (!prompt)
            prompt = "$ ";
        write(1, prompt, my_strlen(prompt));
    }
}