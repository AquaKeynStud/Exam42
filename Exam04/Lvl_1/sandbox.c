/*
Assignment name		:	sandbox
Expected files		:	sandbox.c
Allowed functions	:	fork, waitpid, exit, alarm, sigaction, kill,
						printf, strsignal, errno
===============================================================================

Write the following function:

#include <stdbool.h>
int	sandbox(void (*f)(void), unsigned int timeout, bool verbose)

This function must test if the function f is a nice function or a bad function,
you will return 1 if f is nice , 0 if f is bad or -1 in case of an error in
your function.

A function is considered bad if it is terminated or stopped by a signal
(segfault, abort...), if it exit with any other exit code than 0 or if it
times out.

If verbose is true, you must write the appropriate message among the following:

"Nice function!\n"
"Bad function: exited with code <exit_code>\n"
"Bad function: <signal description>\n"
"Bad function: timed out after <timeout> seconds\n"

You must not leak processes (even in zombie state, this will be checked using
wait).

We will test your code with very bad functions.
*/

// sandbox.c

#include <unistd.h>     // fork(), alarm(), _exit()
#include <sys/wait.h>   // waitpid(), WIFEXITED, WIFSIGNALED, WEXITSTATUS, WTERMSIG
#include <signal.h>     // sigaction, SIGALRM, SIGKILL, struct sigaction
#include <stdbool.h>    // bool
#include <stdio.h>      // printf()
#include <stdlib.h>     // exit()
#include <errno.h>      // errno, EINTR
#include <string.h>     // strsignal()

/* -- Handler pour SIGALRM (on veut pas qu'il termine le parent, on l'intercepte) -- */
static void	do_nothing(int sig)
{
    (void)sig;
}

int sandbox(void (*f)(void), unsigned int timeout, bool verbose)
{
	struct sigaction	sa;
	pid_t				pid;
	pid_t				result;
	int					status;

	pid = fork();							// On crée un enfant qui va servir à executer la commande (enfant pour le tuer au timeout, sans end le prgrm)
	if (pid < 0)							// Si err
		return -1;							// On sort

	/* -- Processus Enfant -- */
	if (pid == 0)
	{
		alarm(timeout);						// On met le timeout, SIGALRM et exit après timeout secondes
		f();								// ON lance la fonction à tester
		_exit(0);							// On exit normalement si son exec est bonne (_exit pour éviter les free des buffers parents...)
	}

	/* -- Processus Parent -- */
	sa = {0};								// On init la struct sigaction à 0
	sa.sa_handler = do_nothing;				// On lui met le handler
	sigemptyset(&sa.sa_mask);				// On lui met aucun mask
	if (sigaction(SIGALRM, &sa, NULL) < 0)	// On initialise le sigaction pour SIGALRM; si err return -1
		return -1;

	alarm(timeout);							// On setup l'alarme dans le parent, qui va lancer SIGALRM après timeout sec

	result = waitpid(pid, &status, 0);		// On récupère le résultat de l'execution de l'enfant

	if (result < 0)							// Si c'est une erreur et que l'enfant n'a pas pu finir (timeout dans le parent)
	{
		if (errno == EINTR)					// Si c'est bien le timeout (code de SIGALRM)
		{
			kill(pid, SIGKILL);				// On tue l'enfant
			waitpid(pid, NULL, 0);			// On récupère l'enfant zombie
			if (verbose)					// On affiche le rapport si besoin
				printf("Bad function: timed out after %u seconds\n", timeout);
			return (0);						// 0 = bad function
		}
		return (-1);						// Si c'est pas le timeout parent, erreur inconnue
	}

	alarm(0);								// L'enfant a fini mais pas le timeout parent: on a le resultat de l'enfant

	if (WIFEXITED(status))					// Sortie normale
	{
		int code = WEXITSTATUS(status);		// On récupère le code de sortie
		if (code == 0)						// Si pas d'erreur (_exit(0))
		{
			if (verbose)					// On affiche si besoin
				printf("Nice function!\n");
			return (1);						// 1 = nice function
		}
		if (verbose)
			printf("Bad function: exited with code %d\n", code);
		return (0);							// Sinon, mauvaise fonction
	}

	if (WIFSIGNALED(status))				// Si l'enfant s'est terminé avec un signal
	{
		int	sig = WTERMSIG(status);
		if (sig == SIGALRM && verbose)
			printf("Bad function: timed out after %u seconds\n", timeout);
		else if (verbose)
			printf("Bad function: %s\n", strsignal(sig));
		return (0);
	}
	return (-1);							// Dans tous les autres cas
}