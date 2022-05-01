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

/**
 * 	@brief	makes the signal ctrl+'\' do nothing
 * 	@NORM	remove pid and system leaks stuff
 */
static void	handle_sigquit(void)
{
	int	pid;

	pid = getpid();
	rl_on_new_line();
	rl_redisplay();
	// for removing '^\'
	write(1, "  \b\b", 4);
	rl_replace_line("", 0);
	printf("%d\n", pid);
	system("leaks minishell");
}

/**
 * 	@brief	handles incoming signals and executes corresponding functions
 * 	@param	sa: signal code
 */
static void	signal_handler(int sa)
{
	if (sa == 2)
		handle_sigint();
	else if (sa == 3)
		handle_sigquit();
}

/**
 * 	@brief	initializes signal handling
 */
void	init_signal_handling(void)
{
	struct sigaction	sa;

	sa.sa_handler = &signal_handler;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}
