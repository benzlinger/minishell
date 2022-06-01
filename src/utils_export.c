/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsiebert <rsiebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:13:20 by rsiebert          #+#    #+#             */
/*   Updated: 2022/06/01 18:13:26 by rsiebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*	@brief	create new head variable if list is empty
 *	@params	name of env var, value of env var
 *	@return	head of list
 */
t_vars	*new_var(char *name, char *value)
{
	t_vars	*head;

	head = malloc(sizeof(t_vars));
	if (!head)
		ft_error(strerror(errno));
	head->name = name;
	if (value)
		head->value = value;
	else
		head->value = NULL;
	head->next = NULL;
	return (head);
}

/**
 *	@brief	get length of environment variable name from *envp[]
 *	@param	environment variable
 *	@return	size of name
 */
int	name_len(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	return (i);
}

/**
 *	@brief	get name of environment variable from *envp[]
 *	@param	environment variable
 *	@return	name of env variable
 */
char	*get_name(char *s)
{
	char	*name;
	int		i;

	if (!s)
		return (NULL);
	name = malloc(name_len(s) + 1);
	if (!name)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != '=')
	{
		name[i] = s[i];
		i++;
	}
	name[i] = '\0';
	return (name);
}

/**
 *	@brief	get value of environment variable from *envp[]
 *	@param	environment variable
 *	@return	value of env variable
 */
char	*get_value(char *s)
{
	char	*value;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	value = malloc(ft_strlen(s) - name_len(s) + 2);
	if (!value)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i] && s[i - 1] != '=')
		i++;
	while (s[i])
	{
		value[j] = s[i];
		i++;
		j++;
	}
	value[i] = '\0';
	return (value);
}

/**	@brief	show list of env variables
 *	@param	head of env variable list
 *	@return	if function scceeded
 */
int	show_vars(t_vars *head, int fd)
{
	t_vars	*tmp;

	if (!head)
	{
		ft_exec_error("List empty.", NULL);
		return (EXIT_FAILURE);
	}
	tmp = head;
	while (tmp)
	{
		write(fd, "declare -x ", 11);
		write(fd, tmp->name, ft_strlen(tmp->name));
		if (tmp->value)
		{
			write(fd, "=\"", 2);
			write(fd, tmp->value, ft_strlen(tmp->value));
			write(fd, "\"", 1);
		}
		write(fd, "\n", 1);
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}
