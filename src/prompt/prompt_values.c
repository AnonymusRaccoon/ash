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
#include <time.h>

char *get_prompt_value4(char c, env_t *env, struct tm *tm)
{
    static char time[11];

    if (c == 't' || c == '@') {
        strftime(time, sizeof(time), "%I:%M%p", tm);
        return (str_tolower(time));
    }
    if (c == 'T') {
        strftime(time, sizeof(time), "%H:%M", tm);
        return (time);
    }
    if (c == 'p') {
        strftime(time, sizeof(time), "%I:%M:%S%p", tm);
        return (str_tolower(time));
    }
    if (c == 'P') {
        strftime(time, sizeof(time), "%H:%M:%S", tm);
        return (time);
    }
    return (time);
}

char *get_prompt_value3(char c, env_t *env)
{
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    static char name[10];

    if (c == 'd') {
        strftime(name, sizeof(name), "%a", tm);
        return (name);
    }
    if (c == 'D')
        return (date_format(tm->tm_mday));
    if (c == 'w') {
        strftime(name, sizeof(name), "%b", tm);
        return (name);
    }
    if (c == 'W')
        return (date_format(tm->tm_mon + 1));
    if (c == 'y')
        return (&tostr(tm->tm_year + 1900)[2]);
    if (c == 'Y')
        return (tostr(tm->tm_year + 1900));
    return (get_prompt_value4(c, env, tm));
}

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
    return (get_prompt_value3(c, env));
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