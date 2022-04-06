/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsiebert <rsiebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 15:41:25 by rsiebert          #+#    #+#             */
/*   Updated: 2021/08/23 21:10:38 by rsiebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*s1;
	char	*out;
	size_t	j;
	size_t	i;

	s1 = (char *)s;
	i = ft_strlen(s1);
	if (len > i)
		len = i;
	out = malloc((len + 1) * sizeof(char));
	if (!out)
		return (NULL);
	j = 0;
	i = 0;
	while (s1[i])
	{
		if (i >= start && j < len)
		{
			out[j] = s1[i];
			j++;
		}
		i++;
	}
	out[j] = '\0';
	return (out);
}
