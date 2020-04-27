/*
** EPITECH PROJECT, 2019
** my_strcapitalize
** File description:
** task10 day06
*/

static int is_previous(char *str, int i, char min, char max)
{
    if (str[0] >= min && str[0] <= max && i == 0)
        return (0);
    else if (str[i - 1] >= min && str[i - 1] <= max)
        return (1);
    else
        return (0);
}

static int to_uppercase(char *str, int i)
{
    int flag = 0;
    int isaz = is_previous(str, i + 1 , 'a', 'z');
    int previousaz = is_previous(str, i, 'a', 'z');
    int previousAZ = is_previous(str, i, 'A', 'Z');
    int previous09 = is_previous(str, i, '0', '9');

    if (previousaz == 0 && previousAZ == 0 && previous09 == 0 && isaz == 1) {
        flag = 1;
    }
    return (flag);
}

static int to_lowercase(char *str, int i)
{
    int flag = 0;
    int isAZ = is_previous(str, i + 1, 'A', 'Z');
    int previousaz = is_previous(str, i, 'a', 'z');
    int previousAZ = is_previous(str, i, 'A', 'Z');
    int previous09 = is_previous(str, i, '0', '9');

    if ((previousaz == 1 || previousAZ == 1 \
        || previous09 == 1) && isAZ == 1)
        flag = 1;
    return (flag);
}

char *my_strcapitalize(char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (to_uppercase(str, i) == 1)
            str[i] = str[i] - 32;
        if (to_lowercase(str, i) == 1)
            str[i] = str[i] + 32;
    }
    return (str);
}
