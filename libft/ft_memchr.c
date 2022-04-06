/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsiebert <rsiebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 13:32:54 by rsiebert          #+#    #+#             */
/*   Updated: 2021/08/26 16:52:37 by rsiebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*str;

	if (n == 0)
		return (NULL);
	str = (char *)s;
	while (--n && *str != (char)c)
		str++;
	if (*str != (char)c)
		return (NULL);
	return (str);
}
