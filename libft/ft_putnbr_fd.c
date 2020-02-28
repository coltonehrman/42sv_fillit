/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cehrman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 17:21:17 by cehrman           #+#    #+#             */
/*   Updated: 2020/02/20 17:47:24 by cehrman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char c;

	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		if (n == MININT)
			ft_putchar_fd('2', fd);
		ft_putnbr_fd((n == MININT) ? ((n + 2000000000) * -1) : n * -1, fd);
	}
	else
	{
		if (n > 9)
			ft_putnbr_fd(n / 10, fd);
		c = (char)((n % 10) + 48);
		ft_putchar_fd(c, fd);
	}
}
