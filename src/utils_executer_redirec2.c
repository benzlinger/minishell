#include "../include/minishell.h"

void	redirec_output(t_token_list *node, bool append)
{
	if (access(node->token, F_OK) == 0)
	{
		if (append)
			node->fd = open(node->token, O_WRONLY | O_APPEND);
		else
			node->fd = open(node->token, O_WRONLY | O_TRUNC);
	}
	else
		node->fd = open(node->token, O_WRONLY | O_CREAT, 0666);
	if (node->fd == -1)
		ft_error(strerror(errno));
	if (dup2(node->fd, STDOUT_FILENO) == -1)
		ft_error(strerror(errno));
	if (close(node->fd) == -1)
		ft_error(strerror(errno));
}

void	redirec_heredoc_input(t_token_list *node)
{
	if (access(".tmp.txt", F_OK) == 0)
		node->fd = open(".tmp.txt", O_RDWR | O_TRUNC);
	else
		node->fd = open(".tmp.txt", O_RDWR | O_CREAT, 0666);
	if (node->fd == -1)
	   ft_error(strerror(errno));
	write(node->fd, node->token, ft_strlen(node->token));
	write(node->fd, "\n", sizeof(char));
	if (close(node->fd) == -1)
		ft_error(strerror(errno));
	node->fd = open(".tmp.txt", O_RDONLY);
	if (dup2(node->fd, STDIN_FILENO) == -1)
		ft_error(strerror(errno));
	if (close(node->fd) == -1)
		ft_error(strerror(errno));
}

void	redirec_input(t_token_list *node)
{
	node->fd = open(node->token, O_RDONLY);
	if (node->fd == -1)
		ft_error(strerror(errno));
	if (dup2(node->fd, STDIN_FILENO) == -1)
		ft_error(strerror(errno));
	if (close(node->fd) == -1)
		ft_error(strerror(errno));
}
