#include <stdio.h>						// printf
#include <unistd.h>						// read
#include <stdlib.h>						// realloc
#include <string.h>						// memmove

#ifndef BUFFER_SIZE
	#define BUFFER_SIZE 1
#endif

void	filter(char *res, char *s)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	while (res[i])						// Tant que res[i] existe
	{
		j = 0;							// On se met au début de s
		if (res[i] == s[j])				// Si la lettre actuelle correspond au début de s
		{
			k = i;						// On garde le i pour fill plus tard

			while (res[k] == s[j])		// Tant que les lettres concordent, on avance
			{
				k++;
				j++;
			}

			if (!s[j])					// Si on est à la fin de s (i.e. on a trouvé s dans res)
			{
				while (i < k)			// Tant que notre i n'a pas rejoint notre "i + strlen(j)" (= k)
					res[i++] = '*';		// On remplace chaque lettre par une '*'
				i--;					// Puisque i++, on dépasse de 1 la fin de s
			}
		}
		i++;			// On passe au caractère suivant si pas de s
	}
	printf("%s", res);	// On affiche le resultat SANS '\n', il est déjà dans res
}

int	main(int ac, char **av)
{
	char	*res;				// Va stocker notre chaîne complète
	char	*backup;			// Sert de protection pour realloc
	int 	total_len;			// Compte le nombre de caractère stockés dans res
	int		bytes_read;			// Compte le nombre de caractères lus avec read
	char	temp[BUFFER_SIZE];	// Stockage pour read

	if (ac != 2)				// Si on a plus d'un argument (en + du pgrm)
		return (1);				// On retourne 1

	res = NULL;
	total_len = 0;
	while ((bytes_read = read(0, temp, BUFFER_SIZE)) > 0)	// On stocke dans temp ce qu'on lit, et dans bytes_read combien on lit
	{
		backup = realloc(res, (total_len + bytes_read + 1));	// On réalloue res à sa taille + le nombre de caractères lus + 1
		if (!backup)
		{
			// perror("realloc");	// Utile que si on demande de renvoyer un message d'erreur
			free(res);
			return (1);
		}
		res = backup;		// On est sûr que l'allocation a fonctionnée. Sans backup, on aurait leak l'ancien res

		memmove((res + total_len), temp, bytes_read);	// On copie temp à la fin de res
		total_len += bytes_read;						// On ajuste la taille de res
		res[total_len] = '\0';							// On null-termine

		if (res[total_len - 1] == '\n')		// Si l'avant dernier est un '\n', on a l'entrée complète
		{
			filter(res, av[1]);				// On va search & replace
			free(res);						// réinitialisation de res pour une nouvelle entrée
			res = NULL;
			total_len = 0;					// réinitialisation de la taille de res pour une nouvelle entrée
		}
	}
	
	if (bytes_read < 0)		// Si on a eu un problème dans la lecture (utile que si on demande de la gestion d'erreurs)
	{
		perror("read");		// On affiche l'erreur
		free(res);
		return (1);
	}

	return (0);
}
