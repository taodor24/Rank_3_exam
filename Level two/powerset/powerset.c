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


/*
another version:
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static void print(int *subtab, int subsize)
{
	for(int i = 0; i < subsize; i++)
	{
		printf("%d", subtab[i]);
		if( i < subsize - 1)
			printf(" ");
	}
	printf("\n");
}
static int calcul(int *subtab, int subsize)
{
	int sum = 0;
	for(int i = 0; i < subsize; i++)
		sum += subtab[i];
	return sum;
}
static void solve(int *tab, int *subtab, int size, int n, int subsize, int level)
{
	if (level == size)
	{	
		if(calcul(subtab, subsize) == n)
			print(subtab, subsize);
		return;
	}
	subtab[subsize] = tab[level];
	solve(tab, subtab, size, n , subsize +1, level +1);
	solve(tab, subtab, size, n , subsize, level +1);
}

int main(int ac, char **av)
{
	if (ac < 2) return 1;
	int size = ac - 2;
	int n = atoi(av[1]);
	int *tab = malloc(sizeof(int) * size);
	if(!tab) {free(tab); return 1;}
	int *subtab = malloc(sizeof(int) * size);
        if(!subtab) {free(subtab); return 1;}
	for(int i = 0; i < size; i++)
		tab[i] = atoi(av[i + 2]);
	solve(tab, subtab, size, n, 0, 0);
	free(tab);
	free(subtab);
	return 0;
}
*/