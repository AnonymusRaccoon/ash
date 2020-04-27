/*
** EPITECH PROJECT, 2019
** my_sort_int_array
** File description:
** task06 day04
*/

void my_sort_int_array(int *array, int size)
{
    int s;
    for (int i = 0; i <= size; i++) {
        if (array[i] > array[i + 1]) {
            s = array[i];
            array[i] = array[i + 1];
            array[i + 1] = s;
        }
    }
    return;
}
