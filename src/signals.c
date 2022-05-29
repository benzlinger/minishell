#include "../include/minishell.h"

/**
 *	@brief	displays a new empty prompt by receiving ctrl+d signal
 */
static void	handle_sigint(void)
{
	rl_on_new_line();
	rl_redisplay();
	// for removing '^C'
	write(1, "  \b\b\n", 5);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

static void	handle_sigint2(void)
{
	rl_on_new_line();
	write(1, "\n", 1);
}

/**
 * 	@brief	makes the signal ctrl+'\' do nothing
 * 	@NORM	remove pid and system leaks stuff
 */
static void	handle_sigquit(void)
{
	int	pid;

	pid = getpid();
	rl_on_new_line();
	//printf("\nPID: %d\n", pid);
	//system("leaks minishell");
	rl_redisplay();
	// for removing '^\'
	write(1, "  \b\b", 4);
	rl_replace_line("", 0);
}

/**
 * 	@brief	handles incoming signals and executes corresponding functions
 * 	@param	sa: signal code
 */
static void	signal_handler(int sig, siginfo_t *info, void *context)
{
	if (sig == 2 && info->si_pid == getpid())
		handle_sigint();
	else if (sig == 2)
		handle_sigint2();
	else if (sig == 3)
		handle_sigquit();
	context = NULL;
}

/**
 * 	@brief	initializes signal handling
 */
void	init_signal_handling(int exit)
{
	struct sigaction	sa;

	// sa.sa_handler = &signal_handler;
	// sa.sa_flags = SA_RESTART;
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = signal_handler;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	exit = 0;
}
