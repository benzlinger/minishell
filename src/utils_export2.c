/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsiebert <rsiebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:13:29 by rsiebert          #+#    #+#             */
/*   Updated: 2022/06/01 18:13:33 by rsiebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**	@brief	find env variable in list by name
 *	@param	name of env var, head of env variable list
 *	@return	if node is found: node, else NULL
 */
int	find_var(char *name, char *value, t_vars *head)
{
	t_vars	*tmp;

	if (!head || !name)
		return (0);
	tmp = head;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, name, ft_strlen(name) + 1))
		{
			if (value)
			{
				if (tmp->value)
					free(tmp->value);
				tmp->value = value;
			}
			free(name);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

/**	@brief	add env variable to list of existing vars
 *	@param	name of var, value of var (can be NULL), head of env variable list
 *	@return	if function succeeded
 */
t_vars	*append_var(char *name, char *value, t_vars *head)
{
	t_vars	*tmp;
	t_vars	*new;

	if (!head)
	{
		head = new_var(name, value);
		return (head);
	}
	if (find_var(name, value, head))
		return (head);
	new = malloc(sizeof(t_vars));
	if (!new)
		ft_error(strerror(errno));
	tmp = head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->name = name;
	if (value)
		new->value = value;
	else
		new->value = NULL;
	new->next = NULL;
	return (head);
}

/**	@brief	initialize list of env variables
 *	@param	env variable list
 *	@return	head of list
 */
t_vars	*init_vars(char **env)
{
	int		i;
	char	*name;
	char	*value;
	t_vars	*head;

	if (!env)
		return (NULL);
	i = 0;
	while (env[i])
	{
		name = get_name(env[i]);
		value = get_value(env[i]);
		head = append_var(name, value, head);
		i++;
	}
	return (head);
}
