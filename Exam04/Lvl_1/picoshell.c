/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   picoshell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 09:52:14 by arocca            #+#    #+#             */
/*   Updated: 2025/10/23 09:56:51 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int picoshell(char **cmds[])
{
	int		i = 0;
	int		in_fd = 0;
	int		ret = 0;
	int		fd[2];
	pid_t	pid;
	int		status;
	int		has_next;

	while (cmds[i])
	{
		has_next = (cmds[i + 1] != NULL);
		if (has_next && pipe(fd) == -1)
			return (1);

		pid = fork();
		if (pid < 0)
		{
			if (has_next)
			{
				close(fd[0]);
				close(fd[1]);
			}
			if (in_fd != 0)
				close(in_fd);
			return (1);
		}

		if (pid == 0) // --- CHILD ---
		{
			if (in_fd != 0)
			{
				dup2(in_fd, STDIN_FILENO);
				close(in_fd);
			}
			if (has_next)
			{
				dup2(fd[1], STDOUT_FILENO);
				close(fd[1]);
				close(fd[0]);
			}
			execvp(cmds[i][0], cmds[i]);
			exit(1);
		}

		// --- PARENT ---
		if (in_fd != 0)
			close(in_fd);
		if (has_next)
		{
			close(fd[1]);
			in_fd = fd[0];
		}
		i++;
	}

	while (wait(&status) > 0)
		if (!WIFEXITED(status) || WEXITSTATUS(status) != 0)
			ret = 1;

	return ret;
}
