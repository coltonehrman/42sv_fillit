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
	t_u16b data;

	data = b_tet->data;
	b_tet->col = col;
	b_tet->row = row;
	s[row++] |= create_btet_row(col, 1, data);
	s[row++] |= create_btet_row(col, 2, data);
	s[row++] |= create_btet_row(col, 3, data);
	s[row] |= create_btet_row(col, 4, data);
}

void	unplace_tet(t_u64b *s, t_tet *b_tet)
{
	t_u16b	data;
	int		row;
	int		col;

	data = b_tet->data;
	row = b_tet->row;
	col = b_tet->col;
	s[row++] ^= create_btet_row(col, 1, data);
	s[row++] ^= create_btet_row(col, 2, data);
	s[row++] ^= create_btet_row(col, 3, data);
	s[row] ^= create_btet_row(col, 4, data);
	b_tet->col = -1;
	b_tet->row = -1;
}

#include <stdio.h>

int		solve_square(int bounds, t_u64b *s, t_tet **b_tets, t_tet **all_btets)
{
	int		col;
	int		row;
	int		i;
	t_u16b	boundsz;
	t_tet	*b_tet;

	boundsz = (0xFFFF >> (16 - bounds));
	i = -1;
	while (b_tets[++i])
	{
		b_tet = b_tets[i];
		row = -1;
		while ((s[row + 1] >> (64 - bounds)) == boundsz && row + 1 < bounds)
			row++;
		while (++row < bounds - b_tet->szy + 1)
		{
			col = -1;
			while (++col < bounds - b_tet->szx + 1)
				if (can_place_tet(col, row, s, (b_tet->data)))
				{
					place_tet(col, row, s, b_tet);
					if (all_tets_placed(all_btets))
						return (1);
					if (solve_square(bounds, s, b_tets + i + 1, all_btets))
						return (1);
					if (b_tet->col > -1 && b_tet->row > -1)
						unplace_tet(s, b_tet);
				}
		}
	}
	return (0);
}
