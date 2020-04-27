/*
** EPITECH PROJECT, 2019
** my_getnbr_base
** File description:
** task19 day06 int nb = my_strlen(str) - 1;
*/

int my_strlen(char const *str);
int my_compute_power_rec(int nb, int power);
void my_put_nbr(int s);
void my_putchar(char c);

static int find_index(char str, char const *base)
{
    for (int i = 0; base[i] != '\0'; i++) {
        if (str == base[i]) {
            return (i);
        }
    }
    return (-1);
}

int my_getnbr_base(char const *str, char const *base)
{
    int sum = 0;
    int i = 0;
    int index;
    int powerneed = my_strlen(str) - 1;
    int basebase = my_strlen(base);
    while (str[i] != '\0') {
        if (str[i] == '-' && str[0] == '-') {
            my_putchar('-');
        }
        else {
            index = find_index(str[i], base);
            sum += (index * my_compute_power_rec(basebase, powerneed - i));
        }
        i++;
    }
    return (sum);
}