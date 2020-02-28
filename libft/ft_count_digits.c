/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_digits.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cehrman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 12:09:36 by cehrman           #+#    #+#             */
/*   Updated: 2020/02/20 12:25:37 by cehrman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_count_digits(int n)
{
	if (n < 0)
	{
		return ((n == MININT) ?
			ft_count_digits((n + 1) * -1) :
			ft_count_digits(n * -1));
	}
	if (n <= 9)
		return (1);
	return (1 + ft_count_digits(n / 10));
}
