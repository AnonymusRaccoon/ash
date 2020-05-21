/*
** EPITECH PROJECT, 2020
** PSU_minishell1_2019
** File description:
** prompt
*/



#include "shell.h"
#include "builtin.h"
#include "redirections.h"
#include "parser.h"
#include "utility.h"
#include <unistd.h>
#include <malloc.h>
#include <string.h>

const builtin builtins[] = {
    {"env", &builtin_env},
    {"setenv", &builtin_setenv},
    {"unsetenv", &builtin_unsetenv},
    {"exit", &builtin_exit},
    {"cd", &builtin_cd},
    {"history", &builtin_history},
    {"which", &builtin_which},
    {"where", &builtin_where},
    {"source", &builtin_source},
    {"alias", &builtin_alias},
    {"unalias", &builtin_unalias},
    {NULL, NULL}
};

int prompt_run(char *cmd, redirection *inout[2], env_t *env)
{
    char **argv = parse_input(cmd, env);

    if (!argv) {
        return (0);
    }
    if (!argv[0])
        return (0);
    argv = globbing(argv);
    if (!argv)
        return (0);
    if (env->window && inout[1] == NULL)
        inout[1] = new_ncurses_pty();
    if (**argv == '!' && argv[0][1] && argv[0][1] != ' ')
        return (run_builtin(&builtins[5], argv, inout, env));
    for (int i = 0; builtins[i].name; i++)
        if (!strcmp(argv[0], builtins[i].name))
            return (run_builtin(&builtins[i], argv, inout, env));
    run_cmd(argv, inout, env);
    free_array(argv);
    return (0);
}

void prompt_prepare(buffer_t *buffer, env_t *env)
{
    char *prompt = my_getenv(env->vars, "PS1");

    if (!prompt)
        prompt = "$ ";
    printf("%s", prompt);
    buffer->startx = strlen(prompt);
}