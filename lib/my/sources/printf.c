/*
** EPITECH PROJECT, 2019
** printf
** File description:
** dezfgergr
*/

#include "../includes/my.h"
#include <stdarg.h>
#include <stdio.h>

int process_mod_extended(char *format, int i, va_list vl)
{
    switch (format[i]) {
    case 'x':
        my_putnbr_base_long(va_arg(vl, unsigned long int), "0123456789abcdef");
        break;
    case 'X':
        my_putnbr_base_long(va_arg(vl, unsigned int), "0123456789ABCDEF");
        break;
    case 'S':
        my_putstr_e(va_arg(vl, char *));
        break;
    case 'h':
        if (format[i - 1] == '%')
            my_put_nbr(va_arg(vl, int));
        i++;
        break;
    default:
        my_putstr("%");
        i--;
    }
    return (i);
}

int process_mod_dlc(char *format, int i, va_list vl)
{
    switch (format[i]) {
    case 'o':
        my_putnbr_base_long(va_arg(vl, unsigned int), "01234567");
        break;
    case 'u':
        my_putnbr_base_long(va_arg(vl, unsigned int), "0123456789");
        break;
    case 'b':
        my_putnbr_base_long(va_arg(vl, unsigned int), "01");
        break;
    case 'p':
        my_putstr("0x");
        my_putnbr_base_long(va_arg(vl, unsigned long int), "0123456789abcdef");
        break;
    default:
        i = process_mod_extended(format, i, vl);
    }
    return (i);
}

int process_mod(char *format, int i, va_list vl)
{
    switch (format[i]) {
    case 'c':
        my_putchar(va_arg(vl, int));
        break;
    case 's':
        my_putstr(va_arg(vl, char *));
        break;
    case 'i':
    case 'd':
        if (format[i - 1] != '%')
            my_putnbr_base_long(va_arg(vl, long int), "0123456789");
        else
            my_put_nbr(va_arg(vl, int));
        break;
    default:
        i = process_mod_dlc(format, i , vl);
    }
    return (i);
}

int process_all(char *format, int i, va_list vl)
{
    switch (format[i]) {
    case 'l':
    case 'j':
    case 't':
    case 'z':
        i = process_mod(format, i + 1, vl);
        break;
    default:
        i = process_mod(format, i, vl);
    }
    i++;
    return (i);
}

int my_printf(char *format, ...)
{
    va_list vl;
    va_start(vl, format);

    for (int i = 0; format[i] != '\0'; i++) {
        if (format[i] == '%')
            i = process_all(format, i + 1, vl);
        if (format[i] == '\0')
            break;
        if (format[i] == '%') {
            i--;
            continue;
        }
        my_putchar(format[i]);
    }
    va_end(vl);
    return (my_strlen(format));
}