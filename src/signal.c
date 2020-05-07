/*
** EPITECH PROJECT, 2020
** PSU_minishell1_2019
** File description:
** my_strsignal
*/

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <malloc.h>
#include <errno.h>
#include <stdlib.h>
#include "utility.h"
#include "shell.h"

const char *my_strsignal(int status)
{
    switch (WTERMSIG(status)) {
    case SIGFPE:
        return ("Floating exception");
    case SIGUSR1:
        return ("User signal 1");
    case SIGUSR2:
        return ("User signal 2");
    case SIGSTKFLT:
        return ("Stack limit exceeded");
    case SIGTRAP:
        return ("Trace/BPT trap");
    case SIGABRT:
        return ("Abort");
    case SIGINT:
        return ("");
    case SIGXFSZ:
        return ("Filesize limit exceeded");
    case SIGVTALRM:
        return ("Virtual time alarm");
    case SIGPROF:
        return ("Profiling time alarm");
    default:
        return strsignal(WTERMSIG(status));
    }
}

void handle_signal(int status, env_t *env)
{
    char *stat;
    const char *err = my_strsignal(status);

    stat = tostr(WEXITSTATUS(status));
    env->vars = my_setenv(env->vars, "?", stat);
    free(stat);
    if (!WIFSIGNALED(status))
        return;
    dprintf(2, "%s %s\nerr", err, WCOREDUMP(status) ? " (core dumped)" : "");
}

void exec_error(char *path, char *cmd)
{
    if (errno == ENOEXEC)
        dprintf(2, "%s: Exec format error. Wrong Architecture.\n", cmd);
    else if (access(path, F_OK) == 0)
        dprintf(2, "%s: Permission denied.\n", cmd);
    else
        dprintf(2, "%s: Command not found.\n", cmd);
    exit(1);
}
