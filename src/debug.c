/* CAUTION
 * This file exists only for debugging purposes
 * and should be removed by the projects completion
 */

#include "../include/minishell.h"

/**
 * ATTENTION! This function should be transfered to libft
 */
char	*ft_color_format_str(char *s, char *pre, char **tofree)
{
	char	*suf;
	char	*out;
	int	i;
	int	j;

	suf = ft_strdup("\e[0m");
	i = ft_strlen(s) + ft_strlen(pre) + ft_strlen(suf);
	out = ft_calloc(i + 1, sizeof(char));
	if (out == NULL)
		ft_error(strerror(errno));
	i = 0;
	j = 0;
	while (pre[i])
	{
		out[j] = pre[i];
		i++;
		j++;
	}
	i = 0;
	while (s[i])
	{
		out[j] = s[i];
		i++;
		j++;
	}
	i = 0;
	while (suf[i])
	{
		out[j] = suf[i];
		i++;
		j++;
	}
	if (tofree != NULL)
		free(*tofree);
	free(suf);
	return (out);
}

void	ft_print_list(t_token_list *head)
{
	t_token_list	*current;

	current = head;
	while (current != NULL)
	{
		printf("pipe_index:\t%i\n", current->pipe_index);
		printf("index:\t\t%i\n", current->index);
		printf("token:\t\t%s\n", current->token);
		printf("type:\t\t%i\n", current->type);
		printf("next:\t\t%p\n", current->next);
		printf("\n");
		current = current->next;
	}
}

void	print_vars(t_vars *head)
{
	t_vars	*tmp;

	tmp = head;
	if (!tmp)
		printf("Empty list.\n");
	while (tmp)
	{
		printf("%s", tmp->name);
		if (tmp->value)
			printf(" =%s", tmp->value);
		printf("\n");
		tmp = tmp->next;
	}
}

void	ft_leaks(void)
{
	system("leaks minishell");
}
