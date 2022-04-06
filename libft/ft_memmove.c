/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsiebert <rsiebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 12:39:00 by rsiebert          #+#    #+#             */
/*   Updated: 2021/08/16 15:46:44 by rsiebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	int		i;
	char	*d;
	char	*s;

	d = (char *)dst;
	s = (char *)src;
	if (d > s)
	{
		i = (int)n - 1;
		while (i >= 0 && dst != NULL)
		{
			d[i] = s[i];
			i--;
		}
	}
	else
	{
		i = 0;
		while (i < (int)n && src != NULL)
		{
			d[i] = s[i];
			i++;
		}
	}
	return (dst);
}
