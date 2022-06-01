/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btenzlin <btenzlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:26:48 by btenzlin          #+#    #+#             */
/*   Updated: 2022/06/01 18:27:49 by btenzlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 *	@brief	displays a new empty prompt by receiving ctrl+d signal
 */
static void	handle_sigint(void)
{
	rl_on_new_line();
	rl_redisplay();
	write(1, "  \b\b\n", 5);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_exitstatus = 1;
}

/**
 * 	@brief	makes the signal ctrl+'\' do nothing
 * 	@NORM	remove pid and system leaks stuff
 */
static void	handle_sigquit(void)
{
	rl_on_new_line();
	rl_redisplay();
	write(1, "  \b\b", 4);
}

/**
 * 	@brief	handles incoming signals and executes corresponding functions
 * 	@param	sa: signal code
 */
static void	signal_handler(int sig, siginfo_t *info, void *context)
{
	if (sig == 2)
		handle_sigint();
	else if (sig == 3)
		handle_sigquit();
	info = NULL;
	context = NULL;
}

/**
 * 	@brief	initializes signal handling
 */
void	init_signal_handling(void)
{
	struct sigaction	sa;

	sa.sa_flags = SA_RESTART;
	sa.sa_sigaction = signal_handler;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}
