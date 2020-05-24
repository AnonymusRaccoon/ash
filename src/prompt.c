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
#include <limits.h>

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
    {"bindkey", &builtin_bindkey},
    {"echo", &builtin_echo},
    {"set", &builtin_set},
    {"unset", &builtin_unset},
    {NULL, NULL}
};

int prompt_run(char *cmd, redirection *inout[2], env_t *env, redirection *cmds)
{
    wordexp_t parser;
    char **argv = parse_input(cmd, env, &parser);
    int ret = -2;

    if (!argv || !argv[0])
        return (0);
    if (**argv == '!' && argv[0][1] && argv[0][1] != ' ')
        ret = run_builtin(&builtins[5], argv, inout, env);
    for (int i = 0; builtins[i].name; i++)
        if (!strcmp(argv[0], builtins[i].name))
            ret = run_builtin(&builtins[i], argv, inout, env);
    if (ret == -2) {
        run_cmd(argv, inout, env);
        ret = 0;
    }
    wordfree(&parser);
    if (cmds)
        free(cmds);
    return (ret);
}

char *minmal_hostname(char *hostname)
{
    int i = 0;

    while (hostname[i] && hostname[i] != '.')
        i++;
    if (hostname[i] == '.')
        hostname[i] = '\0';
    return (hostname);
}

char *get_prompt_value(char c, env_t *env)
{
    static char value[PATH_MAX];

    if (c == '/' || c == '~')
        return (getcwd(value, sizeof(value)));
    if (c == 'n' || c == 'N')
        return (getlogin());
    if (c == 'M' || c == 'm') {
        gethostname(value, sizeof(value));
        if (c == 'm')
            minmal_hostname(value);
        return (value);
    }
    if (c == '%')
        return "%";
    if (c == 'l')
        return (ttyname(STDIN_FILENO));
    if (c == '#') {
        if (!geteuid())
            return ("#");
        return (">");
    }
    if (c == '?')
        return (my_getenv(env->vars, "?"));
    return (NULL);
}

char *parse_prompt(char *prompt, env_t *env)
{
    char *value = NULL;
    int value_length = 0;
    int length = strlen(prompt);

    for (int i = 0; prompt[i]; i++) {
        if (prompt[i] != '%')
            continue;
        value = get_prompt_value(prompt[i + 1], env);
        if (!value)
            continue;
        value_length = strlen(value);
        prompt = realloc(prompt, sizeof(char) * (value_length + length + 2));
        if (!prompt)
            return (NULL);
        rm_n_char(&prompt[i], 2);
        insert_substring(prompt, value, i + 1);
        i += value_length - 1;
        length += value_length - 2;
    }
    return (prompt);
}

void prompt_prepare(buffer_t *buffer, env_t *env)
{
    char *prompt = my_getenv(env->vars, "prompt");

    if (!prompt)
        prompt = "";
    prompt = strdup(prompt);
    prompt = parse_prompt(prompt, env);
    printf("%s", prompt);
    buffer->startx = strlen(prompt);
    free(prompt);
}