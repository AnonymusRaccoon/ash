/*
** EPITECH PROJECT, 2020
** PSU_minishell1_2019
** File description:
** args
*/

#include <unistd.h>
#include <malloc.h>
#include <stdbool.h>
#include <string.h>
#include <shell.h>

int get_arg_count(char *cmd)
{
    int count = 0;

    for (int i = 0; cmd[i]; i++) {
        if (cmd[i] == ' ')
            count++;
    }
    return (count);
}

char **get_argv(char *cmd)
{
    char **argv = calloc(get_arg_count(cmd) + 2, sizeof(char *));

    if (!argv)
        return (NULL);
    argv = split_args(cmd, argv);
    return (argv);
}

char **split_args(char *cmd, char **argv)
{
    int i = 0;
    int j = 0;
    int nb_simple = 0;
    int nb_double = 0;

    for (i = 0; cmd[i]; i++) {
        if (cmd[i] == '\\')
            i += 2;
        nb_simple += cmd[i] == '\'' ? 1 : 0;
        nb_double += cmd[i] == '\"' ? 1 : 0;
        if ((nb_double % 2 == 1 || nb_simple % 2 == 1)
            || (cmd[i] != ' ' && cmd[i] != '\t'))
            continue;
        cmd[i] = '\0';
        if (i > 0)
            argv[j++] = cmd;
        cmd += i + 1;
        i = -1;
    }
    if (i > 0)
        argv[j++] = cmd;
    return (argv);
}

char *get_inhibitor(char *cmd)
{
    bool inhibitor_interpreter = true;

    if (cmd[0] != '\'' && cmd[0] != '\"')
        inhibitor_interpreter = false;
    for (int i = 0; cmd[i]; i++) {
        if (cmd[i] != '\\')
            continue;
        if (inhibitor_interpreter) {
            if (cmd[i + 1] == 'n')
                cmd[i + 1] = '\n';
            if (cmd[i + 1] == 'b')
                cmd[i + 1] = '\b';
            if (cmd[i + 1] == 't')
                cmd[i + 1] = '\t';
            if (cmd[i + 1] == 'v')
                cmd[i + 1] = '\v';
        }
        for (int k = i; cmd[k]; k++)
            cmd[k] = cmd[k + 1];
    }
    return (cmd);
}

char * get_var(char *cmd, env_t *env)
{
    char *isolated_var = NULL;
    char *value = NULL;
    char *new_cmd = NULL;
    int var_len = 0;
    int pos = 0;

    if (cmd[0] == '\'')
        return (cmd);
    for (int i = 0; cmd[i] && !isolated_var; i++)
        if (cmd[i] == '$')
            isolated_var = &cmd[i + 1];
    if (!isolated_var)
        return (cmd);
    if ((isolated_var[0] == ' ' || isolated_var[0] == '\t' || !isolated_var[0]) && cmd[0] != '\"')
        return (cmd);
    if (!(isolated_var[0] >= 'A' && isolated_var[0] <= 'Z')
    && !(isolated_var[0] >= 'a' && isolated_var[0] <= 'z') && isolated_var[0] != '?') {
        printf("Illegal variable name.\n");
        env->vars = my_setenv(env->vars, "?", "1");
        return (NULL);
    }
    for (int i = 0; isolated_var[i] && isolated_var[i] != ' '
    && isolated_var[i] != '\t'; i++)
        var_len++;
    value = get_var_value(isolated_var, env);
    if (!value)
        return ("");
    new_cmd = calloc(strlen(value) + strlen(cmd), sizeof(char));
    for (; cmd[pos] && cmd[pos] != '$'; pos++)
        new_cmd[pos] = cmd[pos];
    for (int i = 0; value[i]; i++)
        new_cmd[pos++] = value[i];
    for (int i = 0; i < (var_len + 1 - (int)strlen(value)); i++)
        new_cmd[pos++] = ' ';
    for (; cmd[pos]; pos++)
        new_cmd[pos] = cmd[pos];
    while (new_cmd[strlen(new_cmd) - 1] == ' ')
        new_cmd[strlen(new_cmd) - 1] = 0;
    return (new_cmd);
}

char *remove_backslash(char *cmd)
{
    for (int i = 0; cmd[i]; i++) {
        if (cmd[i] != '\\')
            continue;
        if (cmd[i + 1] == 'n')
            cmd[i + 1] = '\n';
        if (cmd[i + 1] == 'b')
            cmd[i + 1] = '\b';
        if (cmd[i + 1] == 't')
            cmd[i + 1] = '\t';
        if (cmd[i + 1] == 'v')
            cmd[i + 1] = '\v';
        if (cmd[i + 1] != 'v' && cmd[i + 1] != 'n'
            && cmd[i + 1] != 'b' && cmd[i + 1] != 't')
            cmd[i] = cmd[i + 1];
    }
    return (cmd);
}

char **remove_quotes(char **argv)
{
    int len = 0;
    for (int i = 0; argv[i]; i++) {
        len = strlen(argv[i]);
        if ((argv[i][0] == '\"' && argv[i][len - 1] == '\"')
        || (argv[i][0] == '\'' && argv[i][len - 1] == '\'')) {
            argv[i][len - 1] = 0;
            argv[i]++;
        }
    }
    return (argv);
}

char *get_var_value(char *var, env_t *env)
{
    char *value = my_getenv(env->env, var);

    if (value)
        return (value);
    value = my_getenv(env->vars, var);
    if (value)
        return (value);
    printf("%s: Undefined variable.\n", var);
    env->vars = my_setenv(env->vars, "?", "1");
    return (NULL);
}