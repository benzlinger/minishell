#include "../include/minishell.h"

/**
 * 	@brief creates a file
 */
void	create_file(t_token_list *node)
{
	node->fd = open(node->token, O_RDWR | O_CREAT, 0666);
	if (node->fd == -1)
		ft_error(strerror(errno));
	if (close(node->fd) == -1)
		ft_error(strerror(errno));
}

/**
 * 	@brief	truncates a file
 */
void	truncate_file(t_token_list *node)
{
	node->fd = open(node->token, O_WRONLY | O_TRUNC);
	if (node->fd == -1)
		ft_error(strerror(errno));
	if (close(node->fd) == -1)
		ft_error(strerror(errno));
}

/**
 * 	@brief	redirects, truncates or appends, output to a file
 * 			if it does not exist it is first created
 */
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

/**
 * 	@brief	creates or overwrites a file called .tmp.txt with the contents from
 * 			the heredoc and redirects the file to STDIN
 */
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

/**
 *	@brief	redirects content from node->token to STDIN
 */
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
