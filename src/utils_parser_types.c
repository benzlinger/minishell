/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser_types.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsiebert <rsiebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:16:38 by rsiebert          #+#    #+#             */
/*   Updated: 2022/06/01 18:16:40 by rsiebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * 	@brief	checks for valid pipe syntax
 * 	@param	literal token string of type REDIREC
 * 	@return	0 if syntax is valid
 * 		1 if not
 */
int	type_pipe(char *s)
{
	if (ft_strlen(s) != 1)
	{
		ft_parse_error(s, ": invalid pipe syntax");
		g_exitstatus = 258;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

/**
 * 	@brief	checks for valid redirection syntax
 * 	@param	literal token string of type REDIREC
 * 	@return	0 if syntax is valid
 * 		1 if not
 */
int	type_redirec(char *s)
{
	if (ft_strlen(s) == 1)
		return (EXIT_SUCCESS);
	else if (ft_strlen(s) == 2)
		if (s[0] == '>' && s[1] == '>')
			return (EXIT_SUCCESS);
	ft_parse_error(s, ": invalid redirection syntax");
	g_exitstatus = 258;
	return (EXIT_FAILURE);
}

/**
 * 	@brief	removes single quotes
 * 	@param	pointer to literal token string of type SQUOTE
 * 	@return	string without singlequotes
 */
char	*type_squote(char **s)
{
	char	*out;
	int		i;
	int		j;

	if (quote_count(*s, '\'') % 2 != 0)
	{
		free(*s);
		return (ft_parse_error("odd amount of single quotes", NULL));
	}
	out = ft_calloc(ft_strlen(*s) + 1, sizeof(char));
	if (out == NULL)
		ft_error(strerror(errno));
	i = 0;
	j = 1;
	while (s[0][j] != 39 && s[0][j])
	{
		if (s[0][j] == '|')
			out[i] = 26;
		else
			out[i] = s[0][j];
		i++;
		j++;
	}
	free(*s);
	return (out);
}
