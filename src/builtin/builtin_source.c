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

char **get_arr_from_fd(int fd, char *filepath, char *str)
{
    struct stat st_buff;
    char **arr = NULL;

    stat(filepath, &st_buff);
    str = malloc(st_buff.st_size + 1);
    if (str) {
        read(fd, str, st_buff.st_size);
        arr = split_str(str, '\n');
    }
    return (arr);
}

static void start_script(char **argv, env_t *env, int len_argv)
{
    int fd = open(argv[1], O_RDONLY);
    bool should_close = false;
    char **arr = NULL;
    char *str = NULL;

    if (fd == -1)
        return;
    arr = get_arr_from_fd(fd, argv[1], str);
    if (arr) {
        for (int i = 0; arr[i] && !should_close; i++) {
            if (arr[i][0] == '#')
                continue;
            should_close = (eval_raw_cmd(parse_source_cmd(arr[i],
                            argv, len_argv), env) < 0);
        }
    }
    free(arr);
    free(str);
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
        start_script(argv, env, len);
    return (0);
}