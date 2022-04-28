#include "../include/minishell.h"

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

/**
 *	@brief	get length of environment variable name from *envp[]
 *	@param	environment variable
 *	@return	size of name
 */
int	name_len(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	return (i);
}

/**
 *	@brief	get name of environment variable from *envp[]
 *	@param	environment variable
 *	@return	name of env variable
 */
char	*get_name(char *s)
{
	char	*name;
	int		i;

	if (!s)
		return (NULL);
	name = malloc(name_len(s) + 1);
	if (!name)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != '=')
	{
		name[i] = s[i];
		i++;
	}
	name[i] = '\0';
	return (name);
}

/**
 *	@brief	get value of environment variable from *envp[]
 *	@param	environment variable
 *	@return	value of env variable
 */
char	*get_value(char *s)
{
	char	*value;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	value = malloc(ft_strlen(s) - name_len(s) + 2);
	if (!value)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i] && s[i - 1] != '=')
		i++;
	while (s[i])
	{
		value[j] = s[i];
		i++;
		j++;
	}
	value[i] = '\0';
	return (value);
}

/**	@brief	show list of env variables
 *	@param	head of env variable list
 *	@return	if function scceeded
 */
int	show_vars(t_vars *head)
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
