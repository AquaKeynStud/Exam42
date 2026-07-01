#include "bsq.h"

bool	solve_bsq(info *data)
{
	int		**tmp;
	int		best[3] = {0, 0, 0};

	tmp = calloc(data->height, sizeof(int *));
	if (!tmp)
		return (err("calloc error", NULL));
	
	for (int i = 0; i < data->height; i++)
	{
		tmp[i] = calloc(data->width, sizeof(int));
		if (!tmp[i])
			return (freeTab((char **)tmp, data->height), err("calloc error", NULL));

		for (int j = 0; j < data->width; j++)
		{
			if (data->map[i][j] == data->obstacle)
				tmp[i][j] = 0;
			else if (i == 0 || j == 0)
				tmp[i][j] = 1;
			else
				tmp[i][j] = 1 + min3(tmp[i - 1][j], tmp[i][j - 1], tmp[i - 1][j - 1]);

			if (tmp[i][j] > best[0])
			{
				best[0] = tmp[i][j];
				best[1] = i;
				best[2] = j;
			}
		}
	}

	freeTab((char **)tmp, data->height);

	if (best[0] > 0)
		for (int i = best[1] - best[0] + 1; i <= best[1]; i++)
			for (int j = best[2] - best[0] + 1; j <= best[2]; j++)
				data->map[i][j] = data->full;

	return (true);
}

bool	parse_map(FILE *file, info *data)
{
	char	*line = NULL;
	size_t	cap = 0;
	int		len = 0;

	data->map = calloc(data->height + 1, sizeof(char *));
	if (!data->map)
		return (err("calloc error", NULL));

	for (int i = 0; i < data->height; i++)
	{
		len = getline(&line, &cap, file);
		if (len <= 1 || line[len - 1] != '\n')
			return (free(line), err("map error", data));
		line[--len] = '\0';

		if (i == 0)
			data->width = len;
		else if (len != data->width)
			return (free(line), err("map error", data));

		data->map[i] = calloc(data->width + 1, sizeof(char));
		if (!data->map[i])
			return (free(line), err("calloc error", data));

		for (int j = 0; j < data->width; j++)
		{
			if (line[j] != data->obstacle && line[j] != data->empty)
				return (free(line), err("map error", data));
			data->map[i][j] = line[j];
		}
	}
	free(line);
	return (true);
}

bool	parse_header(FILE *file)
{
	char	*line = NULL;
	size_t	cap = 0;
	int		len = 0;
	info	data;

	len = getline(&line, &cap, file);
	if (len < 5 || line[len - 1] != '\n')
		return (free(line), err("map error", NULL));
	line[--len] = '\0';

	data.height = 0;
	data.full = line[len - 1];
	data.obstacle = line[len - 2];
	data.empty = line[len - 3];

	for (int i = 0; i < len - 3; i++)
	{
		if (line[i] < '0' || line[i] > '9')
			return (free(line), err("map error", NULL));
		data.height = data.height * 10 + line[i] - '0';
	}

	free(line);

	if (data.height <= 0)
		return (err("map error", NULL));
	if (!printable(data.empty) || !printable(data.obstacle) || !printable(data.full))
		return (err("map error", NULL));
	if (data.empty == data.obstacle || data.empty == data.full || data.obstacle == data.full)
		return (err("map error", NULL));

	if (!parse_map(file, &data) || !solve_bsq(&data))
		return (false);

	printTab(&data);
	freeTab(data.map, data.height);

	return (true);
}

int main(int ac, char **av)
{
	FILE	*file;

	if (ac == 1)
		return (!parse_header(stdin));
	else
	{
		for (int i = 1; i < ac; i++)
		{
			file = fopen(av[i], "r");
			if (!file)
			{
				fputs("map error\n", stderr);
				continue ;
			}
			parse_header(file);
			fclose(file);
		}
	}
	return (0);
}
