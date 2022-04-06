/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsiebert <rsiebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 15:41:31 by rsiebert          #+#    #+#             */
/*   Updated: 2021/08/12 12:06:00 by rsiebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_set(char c, char const *set)
{
	int		i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		k;
	char	*out;

	j = 0;
	while (s1[j] && ft_set(s1[j], set))
		j++;
	k = ft_strlen(s1);
	while (k > j && ft_set(s1[k - 1], set))
		k--;
	out = malloc((k - j + 1) * sizeof(char));
	if (!out)
		return (NULL);
	i = 0;
	while (j < k)
	{
		out[i] = s1[j];
		i++;
		j++;
	}
	out[i] = '\0';
	return (out);
}
