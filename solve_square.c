/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_square.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cehrman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 16:44:33 by cehrman           #+#    #+#             */
/*   Updated: 2020/02/28 17:22:58 by cehrman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int	solve_square(int bounds, t_u64b *s, t_tet **b_tets, int call)
{
	int		i;
	int		col;
	int		row;
	int		placed_tet;

	if (count_b_tets(b_tets) == 0)
		return (1);

	i = 0;
	placed_tet = -1;
	while (b_tets[i])
	{
		row = 0;
		while (row < bounds)
		{
			col = 0;
			while (col < bounds)
			{
				if (can_place_tet(col, row, s, b_tets[i]->data))
				{
					placed_tet = i;
					b_tets[i]->col = col;
					b_tets[i]->row = row;

					ft_putstr("\nplacing tet:\nb_tets[");
					ft_putnbr(i);
					ft_putstr("]->data = ");
					print_bin(b_tets[i]->data, 4, 16);
					ft_putstr("\n");

					ft_putstr("b_tets[");
					ft_putnbr(i);
					ft_putstr("]->col = ");
					ft_putnbr(b_tets[i]->col);

					ft_putstr("\nb_tets[");
					ft_putnbr(i);
					ft_putstr("]->row = ");
					ft_putnbr(b_tets[i]->row);
					ft_putstr("\n");

					place_tet(col, row, s, b_tets[i]->data);
					print_overlay(s, 10, bounds, 64);

					--i;
					if (solve_square(bounds, s, ++b_tets, call + 1))
						return (1);

					--b_tets;
					++i;

					ft_putstr("\nun placing tet:\nb_tets[");
					ft_putnbr(placed_tet);
					ft_putstr("]->data = ");
					print_bin(b_tets[placed_tet]->data, 4, 16);
					ft_putstr("\n");

					ft_putstr("b_tets[");
					ft_putnbr(placed_tet);
					ft_putstr("]->col = ");
					ft_putnbr(b_tets[placed_tet]->col);

					ft_putstr("\nb_tets[");
					ft_putnbr(placed_tet);
					ft_putstr("]->row = ");
					ft_putnbr(b_tets[placed_tet]->row);
					ft_putstr("\n");

					unplace_tet(s, b_tets[placed_tet]);
					print_overlay(s, 10, bounds, 64);
				}
				++col;
			}
			++row;
		}
		++i;
	}
	return (0);
}
