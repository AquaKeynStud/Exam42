/*
Exercice : faire un programme qui donne toutes les combinaisons binaires possibles à n<=9 chiffres
*/

#include <stdio.h>

void	backtracking(char *res, int index)
{
	if (res[index] == '\0')
	{
		printf("%s\n", res);
		return ;
	}

	backtracking(res, index + 1);

	if (res[index] == '0')
		res[index] = '1';
	else if (res[index] == '1')
		res[index] = '0';
	else
		return ;

	backtracking(res, index + 1);
}

int	main(int ac, char **av)
{
	int	len;

	if (ac != 2)
		return (1);

	if (*av[1] < '1' || *av[1] > '9' || av[1][1])
		return(1);

	len = *av[1] - '0';
	char	res[len + 1];

	res[len] = '\0';
	while (len--)
		res[len] = '0';
	
	backtracking(res, 0);

	return (0);
}