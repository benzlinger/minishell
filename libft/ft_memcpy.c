/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsiebert <rsiebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 12:35:10 by rsiebert          #+#    #+#             */
/*   Updated: 2021/08/13 12:00:31 by rsiebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*in;
	char	*out;
	size_t	i;

	in = (char *)src;
	out = (char *)dst;
	i = 0;
	while (i < n && (dst != NULL || src != NULL))
	{
		out[i] = in[i];
		i++;
	}
	return (out);
}
