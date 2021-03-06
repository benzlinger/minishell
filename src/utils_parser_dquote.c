/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser_dquote.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsiebert <rsiebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:15:29 by rsiebert          #+#    #+#             */
/*   Updated: 2022/06/01 18:15:33 by rsiebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * 	@brief	checks if an envar is in a string
 * 	@param	s: string to check for envar
 * 	@return	true: a envar
 * 			false: no envar
 */
bool	envar_exists(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '$' && s[i + 1] != '?' && s[i + 1]
			&& s[i + 1] != ' ' && s[i + 1] != '\"')
			return (true);
		i++;
	}
	return (false);
}

/**
 * 	@brief	removes quotes from string
 * 	@param	old: old string to remove quotes from
 * 	@param	new: new string without quotes
 * 	@return 1
 */
static int	remove_quotes(char *old, char *new)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (old[i])
	{
		while (old[i] == '"')
			i++;
		if (old[i] == '|')
			new[j] = 26;
		else
			new[j] = old[i];
		i++;
		j++;
	}
	return (EXIT_SUCCESS);
}

/**
 * 	@brief	counts quotes in string
 * 	@param	s: string to handle
 * 	@return	double quotes count in string s
 */
int	quote_count(char *s, char c)
{
	int	i;
	int	qcount;

	i = 0;
	qcount = 0;
	while (s[i])
	{
		if (s[i] == c)
			qcount++;
		i++;
	}
	return (qcount);
}

/**
 * 	@brief	handles double quotes; removes them and inserts envars
 * 	@param	s: literal token string
 * 	@return converted string
 */
static char	*handle_quotes(char *s)
{
	char	*out;

	out = ft_calloc(ft_strlen(s), sizeof(char));
	if (out == NULL)
		ft_error(strerror(errno));
	if (quote_count(s, '"') % 2 != 0)
	{
		free(out);
		g_exitstatus = 1;
		return (ft_parse_error("odd amount of double quotes", NULL));
	}
	if (remove_quotes(s, out) != 0)
		return (NULL);
	return (out);
}

/**
 * 	@brief	handles double quotes; removes them and inserts envars
 * 	@param	s: pointer to literal token string
 * 	@return converted string
 */
char	*type_dquote(char **s, t_data *data)
{
	char	*out;

	out = handle_quotes(*s);
	if (out == NULL)
	{
		free(*s);
		return (NULL);
	}
	if (has_exitstatus(out))
		out = replace_exitstatus(out);
	if (envar_exists(*s))
		out = insert_envar(&out, data);
	if (out == NULL)
		return (NULL);
	free(*s);
	return (out);
}
