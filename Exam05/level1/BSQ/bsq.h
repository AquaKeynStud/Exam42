#ifndef BSQ_H
# define BSQ_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct	s_info
{
	int 	height;
	char	empty;
	char	obstacle;
	char	full;

	int		width;
	char	**map;
}				info;

bool	printable(char c);
void	printTab(info *data);
int		min3(int a, int b, int c);
bool	err(char *msg, info *data);
void	freeTab(char **tab, int size);

#endif