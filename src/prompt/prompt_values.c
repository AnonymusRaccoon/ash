/*
** EPITECH PROJECT, 2020
** ash
** File description:
** prompt_values
*/

#include "shell.h"
#include "my_ncurses.h"
#include "prompt.h"
#include "key_functions.h"
#include "utility.h"
#include <unistd.h>
#include <limits.h>
#include <stdio.h>

char *get_prompt_value2(char c, env_t *env)
{
    if (c == '?')
        return (my_getenv(env->vars, "?"));
    if (c == '%')
        return ("%");
    if (c == 'B')
        return (prompt_attr(BOLD, false));
    if (c == 'b')
        return (prompt_attr(0, false));
    if (c == 'U')
        return (prompt_attr(UNDERLINE, false));
    if (c == 'u')
        return (prompt_attr(UNDERLINE, true));
    if (c == 'S')
        return (prompt_attr(REVERSE, false));
    if (c == 's')
        return (prompt_attr(REVERSE, true));
    if (c == '!' || c == 'h')
        return (tostr(history_size(env->history)));
    return (NULL);
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
            minimal_hostname(value);
        return (value);
    }
    if (c == 'l')
        return (ttyname(STDIN_FILENO));
    if (c == '#') {
        if (!geteuid())
            return ("#");
        return (">");
    }
    return (get_prompt_value2(c, env));
}