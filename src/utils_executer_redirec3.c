/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_executer_redirec3.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsiebert <rsiebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:12:58 by rsiebert          #+#    #+#             */
/*   Updated: 2022/06/01 18:13:01 by rsiebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*remove_redirec(char **cmd_line, int i, int j)
{
	char	*cmd;
	int		k;

	cmd = ft_calloc(countyy(cmd_line), sizeof(char));
	if (cmd == NULL)
		ft_error(strerror(errno));
	while (cmd_line[i])
	{
		k = 0;
		while (cmd_line[i] && (cmd_line[i][k] == '<' || cmd_line[i][k] == '>'))
			i += 2;
		if (!cmd_line[i])
			break ;
		while (cmd_line[i][k])
		{
			cmd[j] = cmd_line[i][k];
			j++;
			k++;
		}
		cmd[j] = 31;
		j++;
		i++;
	}
	cmd[j] = '\0';
	return (cmd);
}

void	remove_tmp(t_data *data)
{
	char	**cmd_line;
	int		pid;

	if (access(".tmp.txt", F_OK) == 0)
	{
		cmd_line = malloc(sizeof(char *) * 3);
		cmd_line[0] = "/bin/rm";
		cmd_line[1] = ".tmp.txt";
		cmd_line[2] = NULL;
		pid = fork();
		if (pid == -1)
			ft_error(strerror(errno));
		else if (pid == 0)
			execve(cmd_line[0], cmd_line, data->env_list);
		else
		{
			wait(NULL);
			free(cmd_line);
		}
	}
}
