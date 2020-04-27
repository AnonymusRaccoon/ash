/*
** EPITECH PROJECT, 2019
** my_getnbr
** File description:
** Task05 Day04
*/

int my_getnbr(char const *str)
{
    int ret = 0;
    int flag = 1;

    for (int i = 0; str[i] && str[i] != '\n'; i++) {
        ret *= 10;
        if (!(str[i] >= '0' && str[i] <= '9') && str[i] != '-')
            return (0);
        if (str[i] == '-' && i == 0) {
            flag = -1;
            continue;
        }
        else if (str[i] == '-')
            return (0);
        ret += str[i] - 48;
    }
    return (ret * flag);
}