#include "bsq.h"

void	freeTab(char **tab, int size)
{
	if (!tab)
		return ;

	int i = 0;
	while (i < size)
		free(tab[i++]);
	free(tab);
}

bool	err(char *msg, info *data)
{
	if (data)
		freeTab(data->map, data->height);

	fprintf(stderr, "%s\n", msg);
	return (false);
}

void	printTab(info *data)
{
	if (!data)
		return ;
	
	int i = 0;
	while (i < data->height)
		fprintf(stdout, "%s\n", data->map[i++]);
}

int		min3(int a, int b, int c)
{
	return ((a <= b && a <= c) ? a : (b <= c) ? b : c);
}

bool	printable(char c)
{
	return (c >= 32 && c <= 126);
}
