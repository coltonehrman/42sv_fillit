/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_square.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cehrman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 16:44:33 by cehrman           #+#    #+#             */
/*   Updated: 2020/02/29 15:07:32 by cehrman          ###   ########.fr       */
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
		if (b_tets[tet]->col < 0 || b_tets[tet]->row < 0 || col_diff < 0 || row_diff < 0 || col_diff >= 4 || shift >= 15)
		{
			++tet;
			continue;
		}
		/*
		ft_putstr("tet->data: ");
		print_bin(b_tets[tet]->data, 4, 16);
		ft_putstr("\ntet->col: ");
		ft_putnbr(b_tets[tet]->col);
		ft_putstr("\ntet->row: ");
		ft_putnbr(b_tets[tet]->row);
		ft_putstr("\n");
		print_bin(b_tets[tet]->data, 4, 16);
		printf(" [%d] | col_diff: %d row_diff: %d shift: %d\n", tet, col_diff, row_diff, shift);
		*/
		if ((b_tets[tet]->data << shift) & 0x8000)
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
	t_u16b s_section;
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
			s_section = create_section(col, row, s);
			s_section >>= 15;
			s_section <<= 15;
			if (found && (s_section & 0x8000))
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
	int		col;
	int		row;

	if (count_b_tets(b_tets) == 0)
		return (1);

	while (*b_tets)
	{
		row = 0;
		while (row < bounds)
		{
			col = 0;
			while (col < bounds)
			{
				if (can_place_tet(col, row, s, (*b_tets)->data))
				{
					(*b_tets)->col = col;
					(*b_tets)->row = row;
/*
					ft_putstr("\nplacing tet:\nb_tet");
					ft_putstr("->data = ");
					print_bin((*b_tets)->data, 4, 16);
					ft_putstr("\n");

					ft_putstr("b_tet");
					ft_putstr("->col = ");
					ft_putnbr((*b_tets)->col);

					ft_putstr("\nb_tet");
					ft_putstr("->row = ");
					ft_putnbr((*b_tets)->row);
					ft_putstr("\n");
*/

					place_tet(col, row, s, (*b_tets)->data);
/*
					print_overlay(s, 10, bounds, 64);
					print_solution(s, b_tets, bounds);
*/
					if (solve_square(bounds, s, b_tets + 1, call + 1))
						return (1);
/*
					ft_putstr("\nun placing tet:\nb_tet");
					ft_putstr("->data = ");
					print_bin((*b_tets)->data, 4, 16);
					ft_putstr("\n");

					ft_putstr("b_tet");
					ft_putstr("->col = ");
					ft_putnbr((*b_tets)->col);

					ft_putstr("\nb_tet");
					ft_putstr("->row = ");
					ft_putnbr((*b_tets)->row);
					ft_putstr("\n");
*/
					if ((*b_tets)->col > -1 && (*b_tets)->row > -1)
						unplace_tet(s, (*b_tets));
					(*b_tets)->col = -1;
					(*b_tets)->row = -1;
//					print_overlay(s, 10, bounds, 64);
//					print_solution(s, b_tets, bounds);
				}
				++col;
			}
			++row;
		}
		++b_tets;
	}
	return (0);
}
