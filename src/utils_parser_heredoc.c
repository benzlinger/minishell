#include "../include/minishell.h"

char	*type_heredoc(char **s, char *token)
{
	char	*out;
	char	*newline;

	while (ft_strncmp(newline, token, ft_strlen(token) + 1) != 0)
	{
		newline = readline("\e[93mheredoc> \e[0m");
		if (newline == NULL)
			break ;
	}
}
