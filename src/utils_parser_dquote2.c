/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser_dquote2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsiebert <rsiebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:15:36 by rsiebert          #+#    #+#             */
/*   Updated: 2022/06/01 18:15:41 by rsiebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	insert_envar_value2(char *s, char **out, int i, int j)
{
	while (s[i])
	{
		out[0][j] = s[i];
		i++;
		j++;
	}
}

static void	insert_envar_value(char *s, char **out, char *val)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (s[i] != '$')
	{
		out[0][j] = s[i];
		i++;
		j++;
	}
	while (s[i] != ' ' && s[i] != '=' && s[i] != ',' && s[i] != 39 && s[i])
		i++;
	k = 0;
	while (val != NULL && val[k])
	{
		out[0][j] = val[k];
		j++;
		k++;
	}
	insert_envar_value2(s, out, i, j);
}

static char	*get_envar_name(char *s)
{
	int		i;
	int		j;
	char	*out;

	out = ft_calloc(ft_strlen(s), sizeof(char));
	if (out == NULL)
		ft_error(strerror(errno));
	i = 0;
	while (s[i] != '$' && s[i])
		i++;
	i++;
	j = 0;
	while (s[i] != ' ' && s[i] != '=' && s[i] != ',' && s[i] != 39 && s[i])
	{
		out[j] = s[i];
		i++;
		j++;
	}
	return (out);
}

static int	get_envar_info(char *s, char **val, t_data *data)
{
	int		size;
	char	*name;

	name = get_envar_name(s);
	*val = find_env_var_value(data, name);
	size = ft_strlen(s) + ft_strlen(*val) - ft_strlen(name);
	free(name);
	return (size);
}

/**
 * 	@brief	inserts envar into string
 * 			calls it recursively for each envar
 * 	@param	s: pointer to string to insert envars in
 * 	@return string with inserted envar
 */
char	*insert_envar(char **s, t_data *data)
{
	char	*envar_value;
	int		alloc_size;
	char	*out;

	if (has_exitstatus(*s))
		out = replace_exitstatus(*s);
	else
	{
		alloc_size = get_envar_info(*s, &envar_value, data);
		out = ft_calloc(alloc_size + 1, sizeof(char));
		if (out == NULL)
			ft_error(strerror(errno));
		insert_envar_value(*s, &out, envar_value);
		free(*s);
		if (envar_exists(out))
			out = insert_envar(&out, data);
	}
	return (out);
}
