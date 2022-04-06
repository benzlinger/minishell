/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsiebert <rsiebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 16:28:03 by rsiebert          #+#    #+#             */
/*   Updated: 2021/08/23 21:34:24 by rsiebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ministrnstr(char *b, const char *little, size_t i, size_t n)
{
	size_t	k;

	k = 0;
	while (b[i] == little[k] && b[i] != '\0' && i < n)
	{
		i++;
		k++;
	}
	return (k);
}

char	*ft_strnstr(const char *big, const char *little, size_t n)
{
	size_t	i;
	size_t	k;
	char	*b;

	b = (char *)big;
	if (*little == '\0')
		return (b);
	if (n <= 0)
		return (NULL);
	i = 0;
	while (b[i] && i < n)
	{
		if (b[i] == little[0])
		{
			k = ministrnstr(b, little, i, n);
			if (little[k] == '\0')
				return (b + i);
		}
		i++;
	}
	return (NULL);
}
