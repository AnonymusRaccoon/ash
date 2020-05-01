/*
** EPITECH PROJECT, 2020
** ash
** File description:
** builtin source
*/

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "builtin.h"
#include "utility.h"
#include "shell.h"

void start_script(char *path, env_t *env)
{
    char *str = NULL;
    char **arr = NULL;
    int fd = open(path, O_RDONLY);
    bool should_close = false;
    struct stat st_buff;

    if (fd == -1)
        return;
    stat(path, &st_buff);
    str = malloc(st_buff.st_size);
    read(fd, str, st_buff.st_size);
    arr = split_str(str, '\n');
    for (int i = 0; arr[i]; i++) {
        if (should_close)
            break;
        should_close = (eval_raw_cmd(strdup(arr[i]), env) < 0);
    }
    close(fd);
}

bool file_is_accessible(char *path)
{
    struct stat st_buff;

    if (access(path, F_OK)) {
        printf("%s: No such file or directory.\n", path);
        return (false);
    }
    if (stat(path, &st_buff) == -1)
        return (false);
    if (access(path, R_OK)) {
        printf("%s: Permission denied.\n", path);
        return (false);
    }
    if ((st_buff.st_mode & __S_IFMT) == __S_IFDIR) {
        return (false);
    }
    return (true);
}

int builtin_source(char **argv, env_t *env)
{
    int len = 0;

    if (!argv)
        return (0);
    for (; argv[len]; len++);
    if (len == 1) {
        printf("%s: Too few arguments.\n", argv[0]);
        return (0);
    }
    if (file_is_accessible(argv[1]))
        start_script(argv[1], env);
    return (0);
}