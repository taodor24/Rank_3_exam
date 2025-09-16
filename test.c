#include <stdio.h>
#include <stdlib.h>

void    print_subset(int *subset, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (i > 0) printf(" ");
        printf("%d", subset[i]);
    }
    printf("\n");
}

void    backtrack(int *arr, int n, int target, int idx,
                  int *subset, int sub_size, int sum)
{
    if (idx == n) // дошли до конца массива
    {
        if (sum == target)
            print_subset(subset, sub_size);
        return;
    }
    // не берём текущий элемент
    backtrack(arr, n, target, idx + 1, subset, sub_size, sum);

    // берём текущий элемент
    subset[sub_size] = arr[idx];
    backtrack(arr, n, target, idx + 1, subset, sub_size + 1, sum + arr[idx]);
}

int main(int argc, char **argv)
{
    if (argc < 2)
        return (0);

    int target = atoi(argv[1]);
    int n = argc - 2;
    int *arr = malloc(n * sizeof(int));
    int *subset = malloc(n * sizeof(int));

    if (!arr || !subset)
        return (1);

    for (int i = 0; i < n; i++)
        arr[i] = atoi(argv[i + 2]);

    backtrack(arr, n, target, 0, subset, 0, 0);

    free(arr);
    free(subset);
    return (0);
}