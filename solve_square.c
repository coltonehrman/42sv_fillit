/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_square.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cehrman <cehrman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 16:44:33 by cehrman           #+#    #+#             */
/*   Updated: 2020/03/09 02:54:36 by cehrman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

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
		if (b_tets[tet]->col < 0 || b_tets[tet]->row < 0 ||
			col_diff < 0 || row_diff < 0 || col_diff >= 4 || shift >= 15)
		{
			++tet;
			continue ;
		}
		if ((b_tets[tet]->data << shift) & 0x8000)
			return (b_tets[tet]);
		++tet;
	}
	return (0);
}

void	print_solution(t_u64b *s, t_tet **b_tets, int bounds)
{
	t_u16b	s_section;
	t_tet	*found;
	int		row;
	int		col;

	row = 0;
	while (row < bounds)
	{
		col = 0;
		while (col < bounds)
		{
			found = find_tet_in(col, row, b_tets);
			s_section = create_section(col, row, s);
			s_section >>= 15;
			s_section <<= 15;
			if (found && (s_section & 0x8000))
				ft_putchar(found->c);
			else
				ft_putchar('.');
			++col;
		}
		ft_putchar('\n');
		++row;
	}
}

void	place_tet(int col, int row, t_u64b *s, t_tet *b_tet)
{
	t_u64b	b_tet_row[4];
	int		i;

	i = 0;
	b_tet_row[0] = create_btet_row(col, 1, b_tet->data);
	b_tet_row[1] = create_btet_row(col, 2, b_tet->data);
	b_tet_row[2] = create_btet_row(col, 3, b_tet->data);
	b_tet_row[3] = create_btet_row(col, 4, b_tet->data);
	i = 0;
	while (i < 4)
	{
		s[row + i] = s[row + i] | b_tet_row[i];
		++i;
	}
	b_tet->col = col;
	b_tet->row = row;
}

void	unplace_tet(t_u64b *s, t_tet *b_tet)
{
	t_u64b	b_tet_row[4];
	int		i;

	i = 0;
	b_tet_row[0] = create_btet_row(b_tet->col, 1, b_tet->data);
	b_tet_row[1] = create_btet_row(b_tet->col, 2, b_tet->data);
	b_tet_row[2] = create_btet_row(b_tet->col, 3, b_tet->data);
	b_tet_row[3] = create_btet_row(b_tet->col, 4, b_tet->data);
	while (i < 4)
	{
		s[b_tet->row + i] = s[b_tet->row + i] ^ b_tet_row[i];
		++i;
	}
	b_tet->col = -1;
	b_tet->row = -1;
}

#include <stdio.h>

int		solve_square(int bounds, t_u64b *s, t_tet **b_tets, t_tet **all_btets)
{
	int	col;
	int	row;
	int	i;

	//printf("b_tets left: %d\n", count_b_tets(b_tets));
	if (all_tets_placed(all_btets))
	//	if (count_b_tets(b_tets) == 0)
			return (1);
	i = -1;
	while (b_tets[++i])
	{
		row = -1;
		while (++row < bounds)
		{
			col = -1;
			while (++col < bounds)
				if (can_place_tet(col, row, s, (b_tets[i]->data)))
				{
					//printf("placing tet\n");
					place_tet(col, row, s, b_tets[i]);
					//print_overlay(s, bounds, bounds, 64);
					//print_solution(s, all_btets, bounds);
					if (solve_square(bounds, s, b_tets + i + 1, all_btets))
						return (1);
					if (b_tets[i]->col > -1 && b_tets[i]->row > -1)
					{
						//printf("UNplacing tet\n");
						unplace_tet(s, b_tets[i]);
					}
				}
		}
	}
	return (0);
}
