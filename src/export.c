#include "../include/minishell.h"

/**	@brief	find env variable in list by name
 *	@param	name of env var, head of env variable list
 *	@return	if node is found: node, else NULL
 */
static int	find_var(char *name, char *value, t_vars *head)
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
static t_vars	*append_var(char *name, char *value, t_vars *head)
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

/**	@brief	show or create new env variable [with value]
 *	@param	data struct, command line
 *	UNCLEAR: should export test =value work?
 */
int	ft_export(t_data *data, char **cmd_line)
{
	int		i;
	char	*name;
	char	*value;

	if (!data->vars && !cmd_line[1])
		ft_exec_error("List empty.", NULL);
	if (!cmd_line[1])
	{
		data->exitstatus = show_vars(data->vars);
		return (data->exitstatus);
	}
	i = 1;
	while (cmd_line[i])
	{
		if (cmd_line[i][0] == '=')
			ft_exec_error("Not a valid identifier", data);
		else if (cmd_line[i + 1] && cmd_line[i + 1][0] == '=')
		{
			name = ft_strdup(cmd_line[i]);
			value = ft_substr(cmd_line[i + 1], 1, ft_strlen(cmd_line[i + 1]));
			append_var(name, value, data->vars);
			i++;
			data->exitstatus = EXIT_SUCCESS;
		}
		else
		{
			name = ft_strdup(cmd_line[i]);
			append_var(name, NULL, data->vars);
			data->exitstatus = EXIT_SUCCESS;
		}
		i++;
	}
	return (data->exitstatus);
}
