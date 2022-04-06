/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsiebert <rsiebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 16:00:34 by rsiebert          #+#    #+#             */
/*   Updated: 2021/08/12 12:14:03 by rsiebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*str;
	int		nullbyte;

	nullbyte = 0;
	str = (char *)s;
	if (c == '\0')
		nullbyte = 1;
	while (*str || nullbyte)
	{
		if (*str == (char)c)
			return (str);
		else
			str++;
	}
	return (NULL);
}
