#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

int counter;		// Compteur de possibilités, inutile en exam

void	print_chessboard(int boardsize, int chessboard[boardsize])
{
	int		i;
	char	digit;

	i = 0;
	while (i < boardsize - 1)
		printf("%i ", chessboard[i++]);
	printf("%i\n", chessboard[i]);
	counter++;				// Compteur de possibilités, inutile en exam
	return ;
}

bool can_take_pos(int boardsize, int chessboard[boardsize], int current_column, int row)
{
	int	column;

	column = 0;
	while (column < current_column)
	{
		if (chessboard[column] == row)
			return (false);
		if ((chessboard[column] - column) == (row - current_column))
			return (false);
		if ((chessboard[column] + column) == (row + current_column))
			return (false);
		column++;
	}
	return (true);
}

void	backtracking(int boardsize, int chessboard[boardsize], int index, int value)
{
	if (index == boardsize)
		return (print_chessboard(boardsize, chessboard));
	if (value == boardsize)
		return ;
	if (can_take_pos(boardsize, chessboard, index, value))
	{
		chessboard[index] = value;
		backtracking(boardsize, chessboard, index + 1, 0);
		chessboard[index] = -1;
	}
	backtracking(boardsize, chessboard, index, value + 1);
}

int	main(int ac, char **av)
{
	int	i;
	int	boardsize;

	if (ac != 2)
		return (1);

	counter = 0;				// Compteur de possibilités, inutile en exam
	boardsize = atoi(av[1]);

	if (boardsize <= 0)
		return (1);

	i = 0;
	int	chessboard[boardsize];
	while (i < boardsize)
		chessboard[i++] = -1;

	backtracking(boardsize, chessboard, 0, 0);
	printf("%i combinaison possibles trouvées\n", counter);		// Compteur de possibilités, inutile en exam

	return (0);
}
