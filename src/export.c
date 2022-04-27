#include "../include/minishell.h"

//what if list is empty

/*	@brief	show list of env variables
 *	@params	head of env variable list
 *	@return	if function scceeded
 */
static int	show_vars(t_vars *head)
{
	t_vars	*tmp;

	if (!head)
	{
		printf("List empty in export.\n");
		return (EXIT_FAILURE);
	}
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

/*	@brief	find env variable in list by name
 *	@params	name of env var, head of env variable list
 *	@return	if node is found: node, else NULL
 */
static void	find_var(char *name, char *value, t_vars *head)
{
	t_vars	*tmp;

	if (!head || !name)
		return ;
	tmp = head;
	while (tmp)
	{
		if (tmp->name == name)
		{
			if (value)
				tmp->value = value;
			return ;
		}
		tmp = tmp->next;
	}
}

/*	@brief	find env variable in list by name
 *	@params	name of env var, head of env variable list
 *	@return	1 if node is found, 0 if not
 *	FIXME: needs to be executed better (find_var + is_var unnecessary)
 */
static int	is_var(char *name, t_vars *head)
{
	t_vars	*tmp;

	if (!head || !name)
		return (0);
	tmp = head;
	if (tmp->name == NULL)
		return (1);
	while (tmp)
	{
		if (tmp->name == name)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

/*	@brief	add env variable to list of existing vars
 *	@params	name of var, value of var (can be NULL), head of env variable list
 *	@return	if function succeeded
 */
static void	append_var(char *name, char *value, t_vars *head)
{
	t_vars	*tmp;
	t_vars	*new;

	if (!head)
	{
		head = new_var(name, value);
		// printf("%s, %s\n", name, value);
		return ;
	}
	if (is_var(name, head))
	{
		find_var(name, value, head);
		return ;
	}
	new = malloc(sizeof(t_vars));
	if (!new)
		ft_error(strerror(errno));
	tmp = head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->name = name;
	if (value)
		new->value = ft_substr(value, 1, ft_strlen(value));
	else
		new->value = NULL;
	// printf("Name: %s  Value: %s\n", new->name, new->value);
	new->next = NULL;
}

static void	init_vars(t_vars *head, char **env_list)
{
	int		i;
	char	**vars;

	i = 0;
	if (!env_list || !env_list[i])
		return ;
	while (env_list[i])
	{
		vars = ft_split(env_list[i], '=');
		append_var(vars[0], vars[1], head);
		free(vars);
		i++;
	}
}

/*	@brief	show or create new env variable [with value]
 *	@params	command line, head of env variable list
 *	@return	if function scceeded
 *	FIXME	if env var name already exists (assign new value)
 */
void	ft_export(char **cmd_line, t_vars *head, char **env_list)
{
	int			i;
	static int	first;

	if (!first)
		init_vars(head, env_list);
	if (cmd_line[1] && cmd_line[1][0] == '=')
		return ;
	if (!cmd_line[1])
		show_vars(head);
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
		// show_vars(head);
	}
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
t_vars	*ft_unset(char **cmd_line, t_vars *head)
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
