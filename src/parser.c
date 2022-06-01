/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsiebert <rsiebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:09:31 by rsiebert          #+#    #+#             */
/*   Updated: 2022/06/01 18:09:38 by rsiebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	check_tokens_via_type2(t_token_list *cur)
{
	if (cur->type == HEREDOC)
	{
		if (strncmp(cur->token, "<<", 3) != 0)
		{
			ft_parse_error("invalid heredoc syntax near: ", cur->token);
			g_exitstatus = 258;
			return (EXIT_FAILURE);
		}
		if (!cur->next || cur->next->type == HEREDOC
			|| cur->next->type == PIPE || cur->next->type == REDIREC)
		{
			ft_parse_error("Invalid or missing delimiter after: ", cur->token);
		g_exitstatus = 258;
			return (EXIT_FAILURE);
		}
		cur->next->token = type_heredoc(&cur->next->token, cur->next->token);
	}
	if (cur->type == REDIREC)
		if (type_redirec(cur->token) != 0)
			return (EXIT_FAILURE);
	if (cur->type == PIPE)
		if (type_pipe(cur->token) != 0)
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/**
 * 	@brief	runs function depending on tokentype
 * 			and makes them fit for the executer
 * 	@param	head: token list
 * 	@return	1: if an parse error occures
 * 			0: if successful
 */
static int	check_tokens_via_type(t_data *data)
{
	t_token_list	*current;

	current = data->tokens;
	while (current != NULL)
	{
		if (current->type == ENVAR)
			current->token = insert_envar(&current->token, data);
		else if (current->type == DQUOTE)
			current->token = type_dquote(&current->token, data);
		else if (current->type == SQUOTE)
			current->token = type_squote(&current->token);
		if (check_tokens_via_type2(current) != 0)
			return (EXIT_FAILURE);
		if (current->token == NULL)
			return (EXIT_FAILURE);
		current = current->next;
	}
	return (EXIT_SUCCESS);
}

static int	ft_one(t_token_list *node, t_data *data)
{
	if (node->type == PIPE)
	{
		if (node->next == NULL || node->next->type == PIPE)
		{
			ft_parse_error("invalid pipe syntax", NULL);
			g_exitstatus = 258;
			return (EXIT_FAILURE);
		}
		if (node->next->type != BUILTIN)
		{
			node->next->type = COMMAND;
			node->next->token = type_command(&node->next->token, data);
		}
		if (node->next->token == NULL)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

/**
 * 	@brief	the very first token and every token after a pipe gets
 * 			converted to COMMAND unless it's a BUILTIN
 * 	@param	head: head of token list
 * 	@return Success or failure
 */
static int	get_command_types(t_data *data)
{
	t_token_list	*current;

	current = data->tokens;
	if (current->type != BUILTIN)
	{
		current->type = COMMAND;
		current->token = type_command(&current->token, data);
		if (current->token == NULL)
			return (EXIT_FAILURE);
	}
	while (current != NULL)
	{
		if (ft_one(current, data) != 0)
			return (EXIT_FAILURE);
		current = current->next;
	}
	return (EXIT_SUCCESS);
}

/**
 * 	@brief	checks input for errors and returns a rdy-to-run command string
 * 	@param	head: linked list from lexer
 * 	@return	ready-to-run command string
 */
char	*msh_parser(t_data *data)
{
	char	*command;

	set_token_type(data->tokens);
	if (check_tokens_via_type(data) != 0)
		return (NULL);
	if (get_command_types(data) != 0)
		return (NULL);
	if (check_redirections(data->tokens) != 0)
		return (NULL);
	command = ft_list_to_str(data->tokens, 31);
	return (command);
}
