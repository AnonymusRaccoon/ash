/*
** EPITECH PROJECT, 2019
** task01
** File description:
** day10
*/

#ifndef _MY_H_
#define _MY_H_

void my_putchar(char c);
int my_isneg(int nb);
int my_put_nbr(int nb);
void my_swap(int *a, int *b);
int my_putstr(char const *str);
int my_strlen(char const *str);
int my_getnbr(char const *str);
void my_sort_int_array(int *tab, int *size);
int my_compute_power_rec(int nb, int power);
int my_compute_square_root(int nb);
int my_is_prime(int nb);
int my_find_prime_sup(int nb);
char *my_strcpy(char *dest, char const *src);
char *my_strncpy(char *dest, char const *src, int n);
char *my_revstr(char *str);
char *my_strstr(char *str, char const *to_find);
int my_strcmp(char const *s1, char const *s2);
int my_strncmp(char const *s1, char const *s2, int n);
char *my_strupcase(char *str);
char *my_strlowcase(char *str);
char *my_strcapitalize(char *str);
int my_str_isalpha(char const *str);
int my_str_isnum(char const *str);
int my_str_islower(char const *str);
int my_str_isupper(char const *str);
int my_str_isprintable(char const *str);
int my_showstr(char const *str);
int my_showmem(char const *str);
char *my_strcat(char *dest, char const *src);
char *my_strncat(char *dest, char const *src, int nb);
int my_show_word_array(char * const *tab);
char *my_strdup(char const *str);
char **my_str_to_word_array(char const *str);
int sum_stdarg(int mode, int nb, ...);
int disp_stdarg(char *s, ...);
int my_getnbr_base(char const *str, char const *base);
int my_putnbr_base(int nbr, char const *base);
int my_putnbr_base_long(unsigned long long int nbr, char const *base);
void my_putstr_e(char *str);
int my_printf(char *format, ...);
int my_arrlen(void **arr);
int my_get_digit(int nb);
void *my_realloc(char *ptr, int size, int newsize);
int my_str_is_alphanum(const char *str);
char *my_strchr(char *str, char c);
int my_atoi(const char *str);

#endif