/*
** EPITECH PROJECT, 2020
** ash
** File description:
** pty_pipe
*/

#include "redirections.h"
#include "my_ncurses.h"
#include <malloc.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <stddef.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <string.h>
#define _XOPEN_SOURCE 600
#define __USE_XOPEN_EXTENDED
#include <stdlib.h>


const struct redirection_map pty_type = {
    .key = NULL,
    .get_fd = &pyt_get_fd,
    .run_cmd = &pty_get_output,
    .type = OUTPUT | PIPE | EX_PIPE | PTY
};

int pty_open(char **slave_name)
{
    int master = open("/dev/ptmx", O_RDWR | O_NOCTTY);
    int my_errno;

    *slave_name = NULL;
    if (master < 0)
        return (-1);
    if (grantpt(master) < 0 || unlockpt(master) < 0
    || !(*slave_name = ptsname(master))) {
        my_errno = errno;
        close(master);
        errno = my_errno;
        return (-1);
    }
    return (master);
}

struct redirection *new_ncurses_pty(void)
{
    struct redirection *pty = malloc(sizeof(*pty));
    char *slave;

    if (!pty)
        return (NULL);
    pty->type = &pty_type;
    pty->fd = -1;
    pty->extra_data = pty_open(&slave);
    if (pty->extra_data < 0) {
        perror(SHELL_NAME);
        return (pty);
    }
    pty->fd = open(slave, O_RDWR);
    if (pty->fd == -1)
        perror(SHELL_NAME);
    return (pty);
}

int pyt_get_fd(redirection *pty)
{
    struct termios termios;
    struct winsize winsize;

    tcgetattr(0, &termios);
    tcsetattr(pty->fd, TCSANOW, &termios);

    ioctl(0, TIOCGWINSZ, &winsize);
    ioctl(pty->fd, TIOCSWINSZ, &winsize);
    dup2(pty->fd, 2);
    return (pty->fd);
}

void pty_get_output(redirection *pty, env_t *env)
{
    char *line = NULL;
    size_t size = 0;
    FILE *file = fdopen(pty->extra_data, "r");

    close(pty->fd);
    while (getline(&line, &size, file) > 0)
        my_addstr(env->window, line);
    if (line) {
        if (!strchr(line, '\n')) {
            my_attron(BACKGROUND_COLOR, WHITE);
            my_attron(COLOR, BLACK);
            my_addstr(env->window, "%\n");
            my_attrreset();
        }
        free(line);
    }
    fclose(file);
}