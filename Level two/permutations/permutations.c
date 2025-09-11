#include <unistd.h>
#include <stdlib.h>

void putstr(char *s)
{
    int i = 0;
    while (s[i])
        i++;
    write(1, s, i);
    write(1, "\n", 1);
}

void swap(char *s, int i, int j)
{
    char t = s[i];
    s[i] = s[j];
    s[j] = t;
}

int next_perm(char *s, int n)
{
    int i = n - 2;
    while (i >= 0 && s[i] >= s[i + 1])
        i--;
    if (i < 0)
        return 0;
    int j = n - 1;
    while (s[j] <= s[i])
        j--;
    swap(s, i, j);
    for (int a = i + 1, b = n - 1; a < b; a++, b--)
        swap(s, a, b);
    return 1;
}

void sort(char *s, int n)
{
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (s[i] > s[j])
                swap(s, i, j);
}

int main(int ac, char **av)
{
    if (ac != 2)
        return 1;
    int n = 0;
    while (av[1][n])
        n++;
    char *s = malloc(n + 1);
    if (!s) return 1;
    for (int i = 0; i <= n; i++)
        s[i] = av[1][i];
    sort(s, n);
    do {
        putstr(s);
    } while (next_perm(s, n));
    free(s);
    return 0;
}











/*
OLD VERSION: 

#include <unistd.h>
#include <stdlib.h>

void afficher_chaine(char *str)
{
    int len = 0;
    while (str[len])
        len++;
    write(1, str, len);
    write(1, "\n", 1);
}

void swap(char *str, int i, int j)
{
    char tmp = str[i];
    str[i] = str[j];
    str[j] = tmp;
}

void bubble_sort(char *str, int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            if (str[j] > str[j + 1])
                swap(str, j, j + 1);
        }
    }
}


int permutation_suivante(char *str, int len)
{
    int i = len - 2;
    while (i >= 0 && str[i] >= str[i + 1])
        i--;
    if (i < 0)
        return 0;

    int j = len - 1;
    while (str[j] <= str[i])
        j--;
    swap(str, i, j);
    int start = i + 1, end = len - 1;
    while (start < end)
    {
        swap(str, start, end);
        start++;
        end--;
    }
    return 1;
}

int main(int ac, char **av)
{
    if (ac != 2)
        return 1;
    int len = 0;
    while (av[1][len])
        len++;
    char *str = malloc(len + 1);
    if (!str)
        return 1;
    for (int i = 0; i <= len; i++)
        str[i] = av[1][i];
    bubble_sort(str, len);
    do {
        afficher_chaine(str);
    } while (permutation_suivante(str, len));

    free(str);
    return 0;
}
    */