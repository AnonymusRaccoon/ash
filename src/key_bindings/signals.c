/*
** EPITECH PROJECT, 2020
** ash
** File description:
** signals
*/

#include <signal.h>
#include <stddef.h>
#include <unistd.h>
#include "shell.h"
#include "key_functions.h"
#include "my_ncurses.h"

void on_sigint(int sig, siginfo_t *info, void *context)
{
    my_addstr(stdwin, "\n");
}

void on_sigtstp(int sig, siginfo_t *info, void *context)
{
}

void setup_sigint(void)
{
    struct sigaction sa;

    sa.sa_sigaction = &on_sigint;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO;
    sigaction(SIGINT, &sa, NULL);
    sa.sa_sigaction = &on_sigtstp;
    sa.sa_flags = SA_SIGINFO;
    sigaction(SIGTSTP, &sa, NULL);
}

int tty_sigintr_command(int key, buffer_t *buffer, env_t *env)
{
    if (buffer->buffer) {
        buffer->buffer[0] = '\0';
        buffer->pos = 0;
        env->vars = my_setenv(env->vars, "?", "130");
    }
    if (env->window) {
        my_addstr(env->window, "\n");
        prompt_prepare(buffer, env);
    }
    return (0);
}