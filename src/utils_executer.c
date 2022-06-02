/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_executer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btenzlin <btenzlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:12:10 by rsiebert          #+#    #+#             */
/*   Updated: 2022/06/02 10:46:45 by btenzlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_exit_builtin(char **cmd_line)
{
	int	i;

	write(1, "exit\n", 5);
	i = 0;
	if (cmd_line[1])
	{
		while (cmd_line[1][i])
		{
			if (!ft_isdigit(cmd_line[1][i]))
			{
				ft_exec_error("numeric arguments required", NULL);
				return (0);
			}
			i++;
		}
		if (cmd_line[2] && ft_strlen(cmd_line[2]))
		{
			g_exitstatus = 1;
			ft_exec_error("too many arguments", NULL);
			return (1);
		}
		g_exitstatus = ft_atoi(cmd_line[1]);
	}
	return (0);
}

static int	open_rout_file(t_token_list *node, bool append)
{
	int	fd;

	if (access(node->token, F_OK) == 0)
	{
		if (append)
			fd = open(node->token, O_WRONLY | O_APPEND);
		else
			fd = open(node->token, O_WRONLY | O_TRUNC);
	}
	else
		fd = open(node->token, O_WRONLY | O_CREAT, 0666);
	if (fd < 0)
		ft_error(strerror(errno));
	return (fd);
}

int	get_builtin_fd(t_data *data)
{
	t_token_list	*current;
	bool			append;
	int				fd;

	current = iterate_to_current_pipe(data);
	while (current != NULL && current->type != PIPE && current->type != ROUT)
	{
		if (current->type == REDIREC)
			append = set_append(current);
		else if (current->type == TRUNC)
			truncate_file(current);
		else if (current->type == CREAT)
			create_file(current);
		current = current->next;
	}
	if (current != NULL && current->type == ROUT)
		fd = open_rout_file(current, append);
	else
		fd = STDOUT_FILENO;
	return (fd);
}
