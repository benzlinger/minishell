/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsiebert <rsiebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 19:24:13 by rsiebert          #+#    #+#             */
/*   Updated: 2021/08/23 19:26:53 by rsiebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count(long *num)
{
	int	i;
	int	size;

	i = *num;
	size = 1;
	while (i / 10 != 0)
	{
		size++;
		i /= 10;
	}
	if (*num < 0)
	{
		*num *= -1;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	char	*res;
	long	num;
	int		i;
	int		size;

	num = n;
	size = count(&num);
	res = malloc(size * sizeof(char) + 1);
	if (res == NULL)
		return (NULL);
	res[size] = '\0';
	res[0] = '-';
	if (n == 0)
		res[0] = '0';
	i = 1;
	while (num != 0 && i < size + 1)
	{
		res[size - i] = (num % 10) + '0';
		num /= 10;
		i++;
	}
	return (res);
}
