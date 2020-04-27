/*
** EPITECH PROJECT, 2019
** my_strstr
** File description:
** task05 day06
*/

#include <malloc.h>

void *my_realloc(char *ptr, int size, int newsize)
{
    char *new_ptr;

    if (newsize <= size || newsize < 1 || size <= 0)
        return (ptr);
    new_ptr = malloc(newsize);
    if (!new_ptr)
        return (NULL);
    if (ptr) {
        for (int i = 0; i < size; i++)
            new_ptr[i] = ptr[i];
        free(ptr);
    }
    return ((void *)new_ptr);
}