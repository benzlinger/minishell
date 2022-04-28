#include "../include/minishell.h"

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