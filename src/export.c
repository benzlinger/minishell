#include "minishell.h"

//what if list is empty

/*	@brief	show list of env variables
 *	@params	head of env variable list
 *	@return	if function scceeded
 */
static int	show_vars(t_vars *head)
{
	t_vars	*tmp;

	if (!head)
		return (EXIT_FAILURE);
	tmp = head;
	while (tmp)
	{
		printf("declare -x %s", tmp->name);
		if (tmp->value)
			printf("=\"%s\"", tmp->value);
		printf("\n");
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}

/*	@brief	add env variable to list of existing vars
 *	@params	name of var, value of var (can be NULL), head of env variable list
 *	@return	if function succeeded
 */
static int	append_var(char *name, char *value, t_vars *head)
{
	t_vars	*tmp;
	t_vars	*new;

	if (!head)
		return (EXIT_FAILURE);
	tmp = find_var(name, head);
	if (tmp)
	{
		if (value)
			tmp->value = value;
		return (EXIT_SUCCESS);
	}
	new = malloc(sizeof(t_vars));
	if (!new)
		return (EXIT_FAILURE);
	tmp = head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->name = name;
	if (value)
		new->value = value;
	new->next = NULL;
	return (EXIT_SUCCESS);
}

/*	@brief	find env variable in list by name
 *	@params	name of env varr, head of env variable list
 *	@return	if node is found: node, else NULL
 */
static t_vars	*find_var(char *name, t_vars *head)
{
	t_vars	*tmp;

	if (!head || !name)
		return (NULL);
	tmp = head;
	while (tmp)
	{
		if (tmp->name == name)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

/*	@brief	free the whole list of env variables
 *	@params	head of env variable list
 *	@return	if node is found: node, else NULL
 */
static void	free_vars(t_vars *head)
{
	t_vars	*tmp;

	while (head)
	{
		tmp = head->next;
		free(head);
		head = tmp;
	}
}

/*	@brief	show or create new env variable [with value]
 *	@params	command line, head of env variable list
 *	@return	if function scceeded
 *	FIXME	if env var name already exists (assign new value)
 */
static int	ft_export(char **cmd_line, t_vars *head)
{
	int			i;

	if (cmd_line[1][0] == '=')
		return (EXIT_FAILURE);
	if (!cmd_line[1])
	{
		if (!show_vars(head))
			return (EXIT_FAILURE);
	}
	else
	{
		i = 1;
		while (cmd_line[i])
		{
			if (cmd_line[i + 1] && cmd_line[i + 1][0] == '=')
			{
				append_var(cmd_line[i], cmd_line[i + 1], head);
				i++;
			}
			else
				append_var(cmd_line[i], NULL, head);
			i++;
		}
	}
	return (EXIT_SUCCESS);
}

/*	@brief	delete variable from list
 *	@params	name from variable to delete, head of list
 *	@return	(new) head of list
 */
static t_vars	*del_var(char *name, t_vars *head)
{
	t_vars	*tmp;
	t_vars	*prev;

	tmp = head;
	if (tmp->name == name && tmp)
	{
		head = tmp->next;
		free(tmp);
		return (head);
	}
	while (tmp && tmp->name != name)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (!tmp)
		return (head);
	prev->next = tmp->next;
	free(tmp);
	return (head);
}

/*	@brief	remove variable from list
 *	@params	command line, head of list
 *	@return	(new) head of list
 */
static t_vars	*ft_unset(char** cmd_line, t_vars *head)
{
	int	i;

	if (!cmd_line[1] || !head)
		return (head);
	i = 1;
	while (cmd_line[i])
	{
		head = del_var(cmd_line[i], head);
		i++;
	}
	return (head);
}
