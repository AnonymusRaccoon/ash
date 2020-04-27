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
    write(2, err, strlen(err));
    if (WCOREDUMP(status))
        write(2, " (core dumped)", 15);
    write(2, "\n", 1);
}

void exec_error(char *path, char *cmd)
{
    if (errno == ENOEXEC) {
        printf("%s: Exec format error. Wrong Architecture.\n", cmd);
    } else if (access(path, F_OK) == 0) {
        write(2, cmd, strlen(cmd));
        write(2, ": Permission denied.\n", 22);
    } else {
        write(2, cmd, strlen(cmd));
        write(2, ": Command not found.\n", 21);
    }
    exit(1);
}
