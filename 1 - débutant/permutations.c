/*
Exercice : 
	- Afficher toutes les permutations possibles d’un tableau de n chiffres différents :
		• ex pour n = 3 :
			- [1, 2, 3]
			- [1, 3, 2]
			- [2, 1, 3]
			- [2, 3, 1]
			- [3, 1, 2]
			- [3, 2, 1]
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void	print_permutation(int *tab, int len)
{
	int	i;

	i = 0;
	printf("[");
	while (i < len - 1)
		printf("%i, ", tab[i++]);
	printf("%i]\n", tab[len - 1]);
	return ;
}

bool	is_in_tab(int *tab, int index, int value)
{
	int	i;

	i = 0;
	while (i < index)
	{
		if (tab[i++] == value)
			return (true);
	}
	return (false);
}

void	backtracking(int *tab, int index, int len)
{
	int value;

	if (index == len)
		return (print_permutation(tab, len));
	value = 1;
	while (value <= len)
	{
		if (!is_in_tab(tab, index, value))
		{
			tab[index] = value;
			backtracking(tab, index + 1, len);
		}
		value++;
	}
}

int	main(int ac, char **av)
{
	int i;
	int len;

	if (ac != 2)
		return (1);

	len = atoi(av[1]);

	i = 0;
	int	tab[len];
	while (i < len)
		tab[i++] = 0;
	
	backtracking(tab, 0, len);

	return (0);
}