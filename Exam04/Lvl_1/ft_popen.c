/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_popen.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 09:20:52 by arocca            #+#    #+#             */
/*   Updated: 2025/10/28 08:42:53 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>		// Pour pid_t
#include <unistd.h>		// Pour les macros STDS

int	ft_popen(const char *file, char *const argv[], char type)
{
	pid_t	pid;
	int		fd[2];

	if (!file || !argv || (type != 'r' && type != 'w'))	// On vérifie d'abord avoir tous les arguments
		return (-1);

	if (pipe(fd) < 0)									// On crée un pipe (si err: -1 d'où < 0)
		return (-1);

	pid = fork();										// On crée un enfant (pour exec la commande, execvp fait un exit)
	if (pid < 0)										// Si err
		return (close(fd[0]), close(fd[1]), -1);		// On close les fds et on sort avec -1

	/* -- CHILD PROCESS -- */
	if (pid == 0)										// Si on est dans l'enfant
	{
		if (type == 'r')								// Si on est en mode "lecture"
		{
			close(fd[0]);								// On ferme l'entrée (on veut la sortie)
			if (dup2(fd[1], STDOUT_FILENO) < 0)			// On copie la sortie du pipe vers stdout
				exit(1);								// Si err (peu probable: on vérifie le pipe et STDIN et STDOUT sont tjrs valides) on exit
		}
		else											// Sinon, on est en mode écriture
		{
			close(fd[1]);								// On ferme la sortie (on veut l'entrée)
			if (dup2(fd[0], STDIN_FILENO) < 0)			// On copie l'entrée du pipe vers stdin
				exit(1);
		}
		close(fd[0]);									// On ferme les 2 fds dans l'enfant (sécurité, pas de leak)
		close(fd[1]);
		execvp(file, argv);								// On lance execvp dans l'enfant
		exit(1);										// Si fail, execvp n'exit pas, ils faut le faire nous même
	}

	/* -- PARENT PROCESS -- */
	if (type == 'r')									// Si on est en mode lecture
	{
		close(fd[1]);									// On ferme la sortie
		return (fd[0]);									// On retourne l'entrée
	}
	else
	{
		close(fd[0]);									// On ferme la l'entrée
		return fd[1];									// On retourne la sortie
	}
}
