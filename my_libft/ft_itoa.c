/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cehrman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 12:08:09 by cehrman           #+#    #+#             */
/*   Updated: 2020/02/20 12:45:15 by cehrman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	char	*str;
	int		digits;
	int		i;

	digits = ft_count_digits(n);
	if (n < 0)
		digits++;
	str = (char *)malloc(sizeof(char) * (digits + 1));
	if (!str)
		return (0);
	i = 0;
	if (n < 0)
	{
		str[i++] = '-';
		if (n == MININT)
			str[i++] = '2';
		n = (n == MININT) ? (n + 2000000000) * -1 : n * -1;
	}
	str[digits--] = 0;
	while (digits >= i)
	{
		str[digits--] = (char)((n % 10) + 48);
		n /= 10;
	}
	return (str);
}
