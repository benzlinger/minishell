/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsiebert <rsiebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:11:09 by rsiebert          #+#    #+#             */
/*   Updated: 2022/06/01 18:11:11 by rsiebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*	@brief	delete variable from list
 *	@params	name from variable to delete, head of list
 *	@return	(new) head of list
 */
static t_vars	*del_var(char *name, t_vars *head)
{
	t_vars	*tmp;
	t_vars	*prev;

	tmp = head;
	if (!ft_strncmp(tmp->name, name, ft_strlen(name) + 1) && tmp)
	{
		head = tmp->next;
		free(tmp->name);
		free(tmp->value);
		free(tmp);
		return (head);
	}
	while (tmp && ft_strncmp(tmp->name, name, ft_strlen(name) + 1))
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (!tmp)
		return (head);
	prev->next = tmp->next;
	free(tmp->name);
	free(tmp->value);
	free(tmp);
	return (head);
}

/*	@brief	remove variable from list
 *	@params	command line, head of list
 *	@return	(new) head of list
 */
t_vars	*ft_unset(char **cmd_line, t_data *data)
{
	int	i;
	int	is_exit;

	if (!cmd_line[1] || !data->vars)
		return (data->vars);
	i = 1;
	is_exit = 0;
	while (cmd_line[i])
	{
		if (cmd_line[i][0] == '=')
		{
			ft_exec_error("Not a valid identifier", data);
			is_exit = 1;
		}
		else
		{
			data->vars = del_var(cmd_line[i], data->vars);
			if (!is_exit)
				g_exitstatus = EXIT_SUCCESS;
		}
		i++;
	}
	return (data->vars);
}
