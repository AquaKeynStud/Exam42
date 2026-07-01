#include <unistd.h>
#include <sys/wait.h>

int picoshell(char **cmds[])
{
	int		i;
	pid_t	pid;
	int		next;
	int		fd[2];
	int		status;
	int		prev_fd;

	i = 0;
	prev_fd = 0;
	while (cmds[i])
	{
		next = (cmds[i + 1] != NULL);

		if (next && pipe(fd) < 0)
			return (1);

		pid = fork();
		if (pid < 0)
		{
			if (prev_fd)
				close(prev_fd);
			if (next)
			{
				close(fd[0]);
				close(fd[1]);
			}
			return (1);
		}
		
		if (pid == 0)
		{
			if (prev_fd)
			{
				dup2(prev_fd, STDIN_FILENO);
				close(prev_fd);
			}
			if (next)
			{
				dup2(fd[1], STDOUT_FILENO);
				close(fd[0]);
				close(fd[1]);
			}
			execvp(cmds[i][0], cmds[i]);
			exit(1);
		}

		if (prev_fd)
			close(prev_fd);
		if (next)
		{
			close(fd[1]);
			prev_fd = fd[0];
		}
		i++;
	}

	int code = 0;
	while (wait(&status) >= 0)
	{
		if (!WIFEXITED(status) || WEXITSTATUS(status) != 0)
			code = 1;
	}
	return (code);
}