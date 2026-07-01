#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

int count_neighbors(char *board, int width, int height, int x, int y)
{
	int count = 0;

	int neighor_x;
	int neighor_y;

	for (int i = -1; i <= 1; i++)
	{
		neighor_x = x + i;

		if (neighor_x < 0 || neighor_x > width - 1)
			continue;

		for (int j = -1; j <= 1; j++)
		{
			neighor_y = y + j;

			if (neighor_y < 0 || neighor_y > height - 1)
				continue;
			if (i == 0 && j == 0)
				continue;
			
			count += (board[neighor_y * width + neighor_x] == 1);
		}
	}

	return (count);
}

void	print_board(char *board, int width, int height)
{
	int len = width * height;

	for (int i = 0; i < len; i++)
	{
		if (board[i] == 1)
			putchar('O');
		else
			putchar(' ');

		if ((i + 1) % width == 0)
			putchar('\n');
	}
}

void	draw_on_board(char *board, int width, int height)
{
	int		x = 0;
	int		y = 0;
	char	command;
	bool	writing = false;

	while (read(STDIN_FILENO, &command, 1) == 1)
	{
		if (command == 'a')
			x = x > 0 ? x - 1 : 0;
		else if (command == 'd')
			x = x < width - 1 ? x + 1 : width - 1;
		else if (command == 'w')
			y = y > 0 ? y - 1 : 0;
		else if (command == 's')
			y = y < height - 1 ? y + 1 : height - 1;
		else if (command == 'x')
			writing = !writing;
		else
			continue;

		if (writing && (y * width + x) < width * height)
			board[y * width + x] = 1;
	}
}

int main(int ac, char **av)
{
	if (ac != 4)
		return (1);

	int	width = atoi(av[1]);
	int	height = atoi(av[2]);
	int	iterations = atoi(av[3]);
	if (width <= 0 || height <= 0 || iterations < 0)
		return (1);

	char	*board = calloc(width * height, sizeof(char));
	if (!board)
		return (1);

	draw_on_board(board, width, height);

	for (int i = iterations; i > 0; i--)
	{
		char	*new_board = calloc(width * height, sizeof(char));
		if (!new_board)
		{
			free(board);
			return (1);
		}

		for (int j = 0; j < width * height; j++)
		{
			int x = j % width;
			int y = j / width;
			int neighbors = count_neighbors(board, width, height, x, y);

			if (board[j] == 1)
				new_board[j] = (neighbors == 2 || neighbors == 3);
			else if (neighbors == 3)
				new_board[j] = 1;
			else
				new_board[j] = 0;
		}

		free(board);
		board = new_board;
	}
	print_board(board, width, height);

	free(board);
	return (0);
}