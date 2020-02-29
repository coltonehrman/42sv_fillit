/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_square.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cehrman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 16:44:33 by cehrman           #+#    #+#             */
/*   Updated: 2020/02/28 20:45:17 by cehrman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <stdio.h>

t_tet	*find_tet_in(int col, int row, t_tet **b_tets)
{
	int tet;
	int	col_diff;
	int	row_diff;
	int	shift;

	tet = 0;
	while (b_tets[tet])
	{
		col_diff = col - b_tets[tet]->col;
		row_diff = row - b_tets[tet]->row;
		shift = (col_diff + (row_diff * 4));
		if (col_diff < 0 || row_diff < 0 || col_diff >= 4 || shift >= 15)
		{
			++tet;
			continue;
		}
/*
		ft_putstr("tet->data: ");
		print_bin(compress_tet(b_tets[tet]->data), 4, 16);
		ft_putstr("\ntet->col: ");
		ft_putnbr(b_tets[tet]->col);
		ft_putstr("\ntet->row: ");
		ft_putnbr(b_tets[tet]->row);
		ft_putstr("\n");
		print_bin(compress_tet(b_tets[tet]->data), 4, 16);
		printf(" [%d] | col_diff: %d row_diff: %d shift: %d\n", tet, col_diff, row_diff, shift);
*/		
		
		if ((compress_tet(b_tets[tet]->data) << shift) & 0x8000)
			return (b_tets[tet]);
		++tet;
	}
	return (0);
}

/*

AABBE.
AA.BE.
...BE.
CCCCE.
D

*/

void	print_solution(t_u64b *s, t_tet **b_tets, int bounds)
{
	//t_u16b	s_section;
	int		row;
	int		col;

	row = 0;
	while (row < bounds)
	{
		col = 0;
		while (col < bounds)
		{
			//printf("looking for tet in [%d][%d]\n", col, row);
			t_tet *found = find_tet_in(col, row, b_tets);
			if (found)
				ft_putchar(found->c);
			else
				ft_putchar('.');
			//printf("found_tet: %p\n\n", found);
			++col;
		}
		ft_putchar('\n');
		++row;
	}
	s[0] = s[0];
}

int		solve_square(int bounds, t_u64b *s, t_tet **b_tets, int call)
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
/*
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
*/
					place_tet(col, row, s, b_tets[i]->data);
//					print_overlay(s, 10, bounds, 64);

					--i;
					if (solve_square(bounds, s, ++b_tets, call + 1))
						return (1);

					--b_tets;
					++i;
/*
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
*/
					unplace_tet(s, b_tets[placed_tet]);
//					print_overlay(s, 10, bounds, 64);
				}
				++col;
			}
			++row;
		}
		++i;
	}
	return (0);
}
