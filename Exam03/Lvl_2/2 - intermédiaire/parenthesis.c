/*
Exercice :
	- Le programme doit prendre une seul paramètre, qui doit être une suite de parenthèses (ex : "(()")
	- L'utilisateur doit renvoyer la combinaison si elle est correcte :
		• "(())" est correct
		• "(()(())())" est correct
		• "(()()" est incorrect
	- Sinon, il doit renvoyer les combinaison corrigées, avec le maximum de paires (optionnel),
	  en remplaçant les parenthèses en trop par des espaces :
		• "(()" donne :
			- " ()"
			- "( )"
*/


#include <stdio.h>
#include <stdbool.h>

/* -- Optionnel - On stocke en global les variables qui ne changeront pas -- */
char	*input;
int		min_pairs;
/* -- On pourrait les passer en paramètres au backtracking -- */

/* -- Calcule la longueur d'une chaîne -- */
int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int		get_min_pairs(char *s)
{
	int	open;														// on va compter les parenthèses ouvrantes
	int	pairs;														// on va compter les parenthèses fermantes

	open = 0;														// Initialistaion des valeurs
	pairs = 0;
	while (*s)														// Pour chaque caractère
	{
		if (*s == '(')												// Si c'est '('
			open++;													// On ajoute 1 à open
		else if (*s == ')' && open)									// Sinon si c'est ')', et qu'on a des parenthèse ouvertes en attente
		{
			pairs++;												// On a trouvé une paire
			open--;													// Une '(' a trouvé son ')'
		}
		s++;
	}
	return (pairs);
}

/* -- Fonction de backtracking a deux possibilités sur chaque caractère -- */
void	backtracking(char *input, char *s, int index, int open, int close, int pairs)
{
	if (input[index] == '\0')										// On atteint la fin de la chaine: on a trouvé une solution
	{
		if (open == close && pairs == min_pairs)					// On a bien des paires, et le bon nombre
			puts(s);												// On affiche la solution suivie d'un '\n'
		return ;													// On sort de la branche actuelle
	}

	if (input[index] == '(')										// Le caractère est '('
	{
		s[index] = '(';												// On essaye de garder la prenthèse
		backtracking(input, s, index + 1, open + 1, close, pairs);	// On recrée une branche en passant au caractère suivant
		
		// On a fini la boucle récursive en gardant '('

		s[index] = ' ';												// On remplace le caractère par un espace pour essayer le 2e cas
		backtracking(input, s, index + 1, open, close, pairs);		// On recrée une branche, mais en testant avec ' '
	}
	else if (input[index] == ')')									// Le caractère est ')'
	{
		if (open > close)											// Seulement si on a des '(' qui n'ont pas de ')'
		{
			s[index] = ')';											// On essaye de garder la prenthèse
			// Ici, en plus de passer au caractère suivant, on ajoute une paire : une '(' vient de trouver sa ')'
			backtracking(input, s, index + 1, open, close + 1, pairs + 1);
		}

		// On a fini la boucle récursive en gardant ')'

		s[index] = ' ';												// On remplace le caractère par un espace pour essayer le 2e cas
		backtracking(input, s, index + 1, open, close, pairs);		// On recrée une branche, mais en testant avec ' '
	}
	else 															// Ce n'est pas une parenthèse
		return ;													// Erreur dans l'input: on s'arrête
}

/* -- Fonction Principale -- */
int	main(int ac, char **av)
{

	if (ac != 2)						// On vérifie qu'il y ait bien qu'un seul argument donné
		return (1);						// Sinon, on a une erreur

	input = av[1];						// On stocke l'input en global
	min_pairs = get_min_pairs(av[1]);	// On stocke le nombre de paires demandées en global

	if (min_pairs == 0)					// Si aucune paire n'est possible
		return (1);						// On retourne directement

	int	len = ft_strlen(av[1]);			// Calcul de la taille de l'input
	char	s[len + 1];					// On crée une chaine de cette taille (on veut garder l'input intact)

	s[len] = '\0';						// La nouvelle chaine est null-terminée
	while (len--)
		s[len] = ' ';					// Et on remplit la nouvelle chaine d'espaces

	backtracking(av[1], s, 0, 0, 0, 0);	// On lance le backtracking avec :	index, open, close et pairs = 0

	return (0);							// On a retourné toute les possibilitées
}
