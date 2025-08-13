#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int	solution_counter;

void	print_maze(int len, char maze[][len])
{
	int	i;
	int	j;

	i = 0;
	while (i < len)
	{
		j = 0;
		while (j < len - 1)
			printf("%c ", maze[i][j++]);
		printf("%c\n", maze[i][j]);
		i++;
	}
	printf("\n");
	solution_counter++;
	return ;
}

bool	can_step(int len, char maze[][len], int col, int row)
{
	if (col < 0 || row < 0 || col >= len || row >= len)
		return (false);
	if (maze[col][row] != '0')
		return (false);
	return (true);
}

void	backtracking(int len, char maze[][len], int col, int row)
{
	if (col == len - 1 && row == len - 1)
	{
		maze[col][row] = '1';
		print_maze(len, maze);
		maze[col][row] = '0';
		return ;
	}

	if (!can_step(len, maze, col, row))
		return ;

	maze[col][row] = '1';

	backtracking(len, maze, col, row + 1);	// droite
	backtracking(len, maze, col + 1, row);	// bas
	backtracking(len, maze, col, row - 1);	// gauche
	backtracking(len, maze, col - 1, row);	// haut

	maze[col][row] = '0';
}

int	main(int ac, char **av)
{
	int	i;
	int	j;
	int len;

	if (ac != 2)
		return (1);

	len = atoi(av[1]);
	if (len > 9)
		return (1);

	i = 0;
	char	maze[len][len];
	while (i < len)
	{
		j = 0;
		while (j < len)
			maze[i][j++] = '0';
		i++;
	}

	backtracking(len, maze, 0, 0);
	printf("Nombre de solutions trouvées : %i\n", solution_counter);

	return (0);
}