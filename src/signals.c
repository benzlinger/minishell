#include "../include/minishell.h"

//	CTRL+C
static void	handle_sigint(void)
{
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

//	CTRL+Backslash
static void	handle_sigquit(void)
{
	printf("that's ctrl backslash\n");
}

static void	signal_handler(int sa)
{
	if (sa == 2)
		handle_sigint();
	else if (sa == 3)
		handle_sigquit();
}

void	init_signal_handling(void)
{
	struct sigaction	sa;

	sa.sa_handler = &signal_handler;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}
