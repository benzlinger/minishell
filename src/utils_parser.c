/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsiebert <rsiebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:14:55 by rsiebert          #+#    #+#             */
/*   Updated: 2022/06/01 18:18:22 by rsiebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	set_token_type(t_token_list *head)
{
	t_token_list	*current;

	current = head;
	while (current != NULL)
	{
		if (current->next != NULL && current->type == HEREDOC)
			current->next->type = TOKEN;
		current = current->next;
	}
}

/**
 * 	@brief	gets size for allocating command string
 * 	@param	tokens: linked list from lexer
 * 	@return size for command string to be allocated with
 */
static int	get_command_size(t_token_list *tokens)
{
	t_token_list	*current;
	int				listlen;
	int				charlen;

	current = tokens;
	listlen = 0;
	charlen = 0;
	while (current != NULL)
	{
		charlen += ft_strlen(current->token);
		listlen++;
		current = current->next;
	}
	return (listlen + charlen);
}

/**
 * 	@brief	norm function; also setting the delimiter for command string
 * 	@param	command: pointer to command string
 * 	@param	i: pointer to index
 * 	@param	c: the delimiter to set (standard is space ' ')
 */
static void	add_delimiter(char **command, int *i, char c)
{
	command[0][*i] = c;
	*i += 1;
}

/**
 * 	@brief	turns the token list into a single string with a set delimiter
 * 	@param	tokens: linked list from lexer
 * 	@param	c: the delimiter to set (standard is space ' ')
 * 	@return	command string
 */
char	*ft_list_to_str(t_token_list *tokens, char c)
{
	t_token_list	*current;
	char			*command;
	int				size;
	int				i;
	int				j;

	size = get_command_size(tokens);
	command = ft_calloc(size + 1, sizeof(char));
	if (command == NULL)
		ft_error(strerror(errno));
	current = tokens;
	i = 0;
	while (current != NULL)
	{
		j = 0;
		while (current->token[j])
		{
			command[i] = current->token[j];
			i++;
			j++;
		}
		add_delimiter(&command, &i, c);
		current = current->next;
	}
	return (command);
}
