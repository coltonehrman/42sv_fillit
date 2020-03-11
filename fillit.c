/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cehrman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 14:08:06 by cehrman           #+#    #+#             */
/*   Updated: 2020/03/01 16:44:49 by cehrman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
** DONTDELETE
*/

t_u16b	tet_to_bin(char *tet)
{
	t_u16b	bin;
	int		x;

	bin = 0;
	x = 0x8000;
	while (*tet)
	{
		if (*tet == '#')
			bin += x;
		x = x >> 1;
		tet++;
	}
	return (compress_tet(bin));
}

/*
** DONTDELETE
*/

void	free_matrix(char ***matrix)
{
	int	i;

	i = 0;
	while ((*matrix)[i])
	{
		free((*matrix)[i]);
		(*matrix)[i] = 0;
		i++;
	}
	free(*matrix);
	*matrix = 0;
}

/*
** DONTDELETE
*/

t_u8b	get_row_of_tet(t_u16b tet, int row)
{
	tet = tet >> ((4 - row) * 4);
	return (tet & 15);
}

/*
** DONTDELETE
*/

int		can_shift_tet(t_u16b tet)
{
	t_u8b	row[4];

	row[0] = get_row_of_tet(tet, 1);
	row[1] = get_row_of_tet(tet, 2);
	row[2] = get_row_of_tet(tet, 3);
	row[3] = get_row_of_tet(tet, 4);
	return (!(row[0] & 0x08) && !(row[1] & 0x08) &&
			!(row[2] & 0x08) && !(row[3] & 0x08));
}

/*
** DONTDELETE
*/

t_u16b	compress_tet(t_u16b tet)
{
	t_u16b	shifted;
	t_u8b	row[4];
	int		i;

	shifted = tet;
	row[0] = get_row_of_tet(tet, 1);
	row[1] = get_row_of_tet(tet, 2);
	row[2] = get_row_of_tet(tet, 3);
	row[3] = get_row_of_tet(tet, 4);
	i = 0;
	while (i < 4)
	{
		if (!(row[i]))
			shifted <<= 4;
		else
			break ;
		i++;
	}
	while (can_shift_tet(shifted))
		shifted <<= 1;
	return (shifted);
}

/*
** DONTDELETE
*/

void	init_overlay(t_u64b *s, int size)
{
	while (size-- > 0)
		s[size] = 0x0;
}

void	create_tet_overlay(t_u64b *overlay, t_u16b b_tet)
{
	t_u64b	row;
	int		i;

	init_overlay(overlay, 64);
	b_tet = compress_tet(b_tet);
	i = 0;
	while (i < 4)
	{
		row = 0x0;
		row = get_row_of_tet(b_tet, i + 1);
		row <<= 60;
		overlay[i++] = row;
	}
}

/*
** DONTDELETE
*/

int		calc_min_square_size(int total_bits)
{
	int	square;

	square = 2;
	while ((square * square) < total_bits)
		square++;
	return (square);
}

/*
** DONTDELETE
*/

t_u16b	create_section(int col, int row, t_u64b *s)
{
	t_u16b	temp;
	t_u16b	section;

	section = 0;
	temp = s[row] >> (60 - col);
	section = section | (temp << 12);
	temp = s[row + 1] >> (60 - col);
	temp <<= 12;
	section = section | (temp >> 4);
	temp = s[row + 2] >> (60 - col);
	temp <<= 12;
	section = section | (temp >> 8);
	temp = s[row + 3] >> (60 - col);
	temp <<= 12;
	section = section | (temp >> 12);
	return (section);
}

/*
** DONTDELETE
*/

int		can_place_tet(int col, int row, t_u64b *s, t_u16b b_tet)
{
	t_u16b	b_section;

	b_section = create_section(col, row, s);
	return (!(b_tet & b_section));
}

/*
** DONTDELETE
*/

t_u64b	create_btet_row(int col, int row, t_u16b b_tet)
{
	t_u64b	b_tet_row;

	b_tet_row = (b_tet >> ((4 - row) * 4)) & 15;
	b_tet_row <<= (60 - col);
	return (b_tet_row);
}

/*
** DONTDELETE
*/

int		count_b_tets(t_tet **b_tets)
{
	int i;

	i = 0;
	while (b_tets[i++])
		;
	return (i - 1);
}

/*
** DONTDELETE
*/

int		get_num_strings(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i++])
		;
	return (i - 1);
}

/*
** DONTDELETE
*/

void	add_bounds_to_square(t_u64b *s, int bounds)
{
	t_u64b	col_mask;
	t_u64b	row_mask;
	int		i;

	row_mask = 0xFFFFFFFFFFFFFFFF;
	col_mask = row_mask >> bounds;
	i = 0;
	while (i < 64)
	{
		if (i < bounds)
			s[i] = col_mask;
		else
			s[i] = row_mask;
		++i;
	}
}
