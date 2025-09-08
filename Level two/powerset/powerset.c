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


