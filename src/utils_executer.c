#include "../include/minishell.h"

static int	open_rout_file(t_token_list *node, bool append)
{
	int	fd;

	if (access(node->token, F_OK) == 0)
	{
		if (append)
			fd = open(node->token, O_WRONLY | O_APPEND);
		else
			fd = open(node->token, O_WRONLY | O_TRUNC);
	}
	else
		fd = open(node->token, O_WRONLY | O_CREAT, 0666);
	if (fd < 0)
		ft_error(strerror(errno));
	return (fd);
}

int	get_builtin_fd(t_data *data)
{
	t_token_list	*current;
	bool			append;
	int				fd;

	current = iterate_to_current_pipe(data);
	while (current != NULL && current->type != PIPE && current->type != ROUT)
	{
		if (current->type == REDIREC)
			append = set_append(current);
		else if (current->type == TRUNC)
			truncate_file(current);
		else if (current->type == CREAT)
			create_file(current);
		current = current->next;
	}
	if (current != NULL && current->type == ROUT)
		fd = open_rout_file(current, append);
	else
		fd = STDOUT_FILENO;
	return (fd);
}
