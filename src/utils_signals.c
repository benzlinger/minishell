/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_signals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btenzlin <btenzlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:27:10 by btenzlin          #+#    #+#             */
/*   Updated: 2022/06/01 18:27:19 by btenzlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	child_handler(int sig, siginfo_t *info, void *context)
{
	if (sig == 2)
		write(1, "\n", 1);
	else if (sig == 3)
		write(1, "Quit: 3\n", 8);
	info = NULL;
	context = NULL;
}

void	init_child_handling(void)
{
	struct sigaction	sa;

	sa.sa_flags = SA_RESTART;
	sa.sa_sigaction = child_handler;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}
