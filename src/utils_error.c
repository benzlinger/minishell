#include "../include/minishell.h"

int	ft_error(int status)
{
	if (status == ALLOC)
		write(2, ERROR"A dynamic memory allocation failed.", 42);
	return (status);
}
