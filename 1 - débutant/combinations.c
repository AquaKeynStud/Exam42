/*
Exercice : Ecrire un programme qui prend 2 paramètres n et k:
				- n = max du chiffre dans la combinaison
				- k = taille de la combinaison
			Donner toutes les combinaisons possibles des k chiffres allants de 1 à n.

			ex : n = 4, k = 2:
				Solutions : 12 13 14 23 24 34

			On ne prend pas 21 ou 42, car on a déjà 12 et 24 (combinaisons != permutations)
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int solution_count;

void	print_combination(int *tab, int tab_len)
{
	int	i;

	i = 0;
	while (i < tab_len)
		printf("%i", tab[i++]);
	printf("\n");
	solution_count++;
	return ;
}

bool	isnt_used(int *tab, int index, int value)
{
	int	i;

	i = 0;
	while (i < index)
	{
		if (tab[i++] == value)
			return (false);
	}
	return (true);
}

void	backtracking(int *tab, int max_value, int tab_len, int index, int value)
{
	if (index == tab_len)
		return (print_combination(tab, tab_len));

	if (value > max_value)
		return ;
	
	if (isnt_used(tab, index, value))
	{
		tab[index] = value;
		backtracking(tab, max_value, tab_len, index + 1, value + 1);
	}
	backtracking(tab, max_value, tab_len, index, value + 1);
}

int	main(int ac, char **av)
{
	int	i;
	int	n;
	int	k;

	if (ac != 3)
		return (1);

	solution_count = 0;
	
	i = 1;
	while (i < 3)
	{
		if (atoi(av[i]) > 9 || atoi(av[i]) < 0)
			return (1);
		i++;
	}
	n = atoi(av[1]);
	k = atoi(av[2]);

	i = 0;
	int tab[k];
	while (i < k)
		tab[i++] = 0;

	backtracking(tab, n, k, 0, 1);
	printf("Nombre de solutions trouvées : %i\n", solution_count);

	return (0);
}