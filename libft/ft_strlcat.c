/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsiebert <rsiebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 15:08:49 by rsiebert          #+#    #+#             */
/*   Updated: 2021/08/23 19:23:15 by rsiebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t n)
{
	size_t	i;
	size_t	j;
	size_t	d_len;
	size_t	s_len;
	char	*s;

	s = (char *)src;
	s_len = ft_strlen(src);
	i = 0;
	j = ft_strlen(dst);
	d_len = j;
	if (n == 0)
		return (ft_strlen(s));
	if (n <= d_len)
		return (s_len + n);
	while (s[i] && i + j < n - 1)
	{
		dst[j + i] = s[i];
		i++;
	}
	dst[j + i] = '\0';
	return (s_len + d_len);
}
