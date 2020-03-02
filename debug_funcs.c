/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cehrman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 16:59:12 by cehrman           #+#    #+#             */
/*   Updated: 2020/03/01 16:59:43 by cehrman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	print_bin(t_u64b n, int bounds, int size)
{
	t_u64b	x;
	int		i;
	int		prints;

	x = 0x1;
	i = size;
	while (--size)
		x <<= 1;
	prints = 0;
	while (i--)
	{
		prints++;
		if (x & n)
			ft_putnbr(1);
		else
			ft_putnbr(0);
		if (prints == bounds && i != 0)
		{
			ft_putchar(' ');
			prints = 0;
		}
		x >>= 1;
	}
}

void	print_overlay(t_u64b *overlay, int rows, int bounds, int size)
{
	int	i;

	i = 0;
	while (i < rows)
	{
		print_bin(overlay[i++], bounds, size);
		ft_putchar('\n');
	}
	ft_putchar('\n');
}
