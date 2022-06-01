/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsiebert <rsiebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:10:26 by rsiebert          #+#    #+#             */
/*   Updated: 2022/06/01 18:10:28 by rsiebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	ft_one(char **cmd_array, char ***cmds, int j)
{
	if (!ft_strncmp(cmd_array[j], "export", 6))
		cmds[j] = export_cmd(cmd_array[j]);
	else if (!ft_strncmp(cmd_array[j], "unset", 5))
		cmds[j] = export_cmd(cmd_array[j]);
	else
		cmds[j] = ft_split(cmd_array[j], 31);
	return (j + 1);
}

void	check_for_substitute_char(char **cmd_array)
{
	int	i;
	int	j;

	i = 0;
	while (cmd_array[i])
	{
		j = 0;
		while (cmd_array[i][j])
		{
			if (cmd_array[i][j] == 26)
				cmd_array[i][j] = '|';
			j++;
		}
		i++;
	}
}

/**	@brief	parse commandline with pipes into seperate commands
 *	@param	cmd_line command line
 *	@return	3d array with commands
 */
char	***get_cmds(char *cmd_line)
{
	char	**cmd_array;
	char	***cmds;
	int		i;
	int		j;

	cmd_array = ft_split(cmd_line, '|');
	check_for_substitute_char(cmd_array);
	if (!cmd_array)
		ft_error(strerror(errno));
	i = 0;
	while (cmd_array[i])
		i++;
	cmds = malloc(sizeof(char **) * i + 1);
	if (!cmds)
		ft_error(strerror(errno));
	j = 0;
	while (j < i)
		j = ft_one(cmd_array, cmds, j);
	cmds[j] = NULL;
	free_2d_array(cmd_array);
	i = 0;
	return (cmds);
}
