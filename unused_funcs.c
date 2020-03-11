/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unused_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cehrman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 16:48:37 by cehrman           #+#    #+#             */
/*   Updated: 2020/03/01 16:59:02 by cehrman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		number_of_tets(char *tetriminos)
{
	char	**tets;
	int		i;

	tets = ft_strsplit(tetriminos, '\n');
	i = 0;
	while (tets[i++])
		;
	free_matrix(&tets);
	return (i - 1);
}

int		left_most_bit(t_u64b n)
{
	int	pos;

	pos = 65;
	while (pos-- > 0)
	{
		if (0x8000000000000000 & n)
			return (pos);
		n <<= 1;
	}
	return (-1);
}

int		get_size(int bit_count)
{
	int	size;

	size = 2;
	while ((size * size) <= bit_count)
		size++;
	return (size);
}

t_u16b	shift_to_corner(t_u16b corner, t_u16b tet)
{
	t_u16b shifted;

	shifted = tet;
	while (!(shifted & corner))
		shifted = shifted << 1;
	return (shifted);
}

void	print_overlays(t_u64b *s, int s_size, t_u64b **layers, t_u64b col_b, int row_b)
{
	t_u64b	col;
	int		printed_char;
	int		i;
	int		j;

	i = 0;
	while (i < s_size && i < row_b)
	{
		col = 0x8000000000000000;
		while (col)
		{
			j = 0;
			printed_char = 0;
			while (layers[j] && !(col & col_b))
			{
				if ((s[i] & col) && (layers[j][i] & col))
				{
					ft_putchar((char)(j + 65));
					printed_char = 1;
				}
				j++;
			}
			if (!(col & col_b) && !printed_char)
				ft_putchar('.');
			col >>= 1;
		}
		ft_putchar('\n');
		i++;
	}
}

int		find_next_col(t_u64b s_row)
{
	t_u64b	mask;
	int		pos;

	mask = 0x8000000000000000;
	pos = 0;
	while ((s_row & mask) && pos != 63)
	{
		mask >>= 1;
		pos++;
	}
	return ((pos == 63) ? -1 : pos);
}


/*int		can_place_tet_in_row(int row, int bounds, t_u64b *s, t_u16b b_tet)
{
	t_u16b	b_section;
	int		i;

	i = 0;
	b_tet = compress_tet(b_tet);
	while (i < bounds)
	{
		b_section = create_section(i, row, s);
		++i;
		if (!(b_tet & b_section))
			return (1);
	}
	return (0);
}*/

/*int		can_place_tet_in_square(int bounds, t_u64b *s, t_u16b b_tet)
{
	t_u16b	b_section;
	int		i;
	int		row;

	row = 0;
	b_tet = compress_tet(b_tet);
	while (row < bounds)
	{
		i = 0;
		while (i < bounds)
		{
			b_section = create_section(i, row, s);
			if (!(b_tet & b_section))
				return (1);
			++i;
		}
		++row;
	}
	return (0);
}*/

/*int		overlays_overlap(t_u64b *o1, t_u64b *o2, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (o1[i] & o2[i])
			return (1);
		i++;
	}
	return (0);
}

int		in_col_bounds(t_u64b *overlay, t_u64b col_bounds, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (overlay[i] & col_bounds)
			return (0);
		i++;
	}
	return (1);
}

int		in_row_bounds(t_u64b *overlay, int row_bounds, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if ((overlay[i] & 0xFFFFFFFFFFFFFFFF) && i >= row_bounds)
			return (0);
		i++;
	}
	return (1);
}

int		in_bounds(t_u64b *overlay, t_u64b col_bounds, int row_bounds)
{
	return (in_col_bounds(overlay, col_bounds, 64)
			&& in_row_bounds(overlay, row_bounds, 64));
}

void	shift_tet_overlay_down(t_u64b *overlay, int size)
{
	t_u64b	prev;
	t_u64b	curr;
	t_u64b	next;
	int		i;

	i = 0;
	prev = 0x0;
	curr = overlay[i];
	while (i < (size - 1))
	{
		curr = overlay[i];
		next = overlay[i + 1];
		overlay[i] = prev;
		overlay[i + 1] = curr;
		prev = overlay[i + 2];
		overlay[i + 2] = next;
		i += 3;
	}
}

int		shift_tet_overlay_right(t_u64b *overlay, int size)
{
	int	i;

	i = 0;
	while (i < size)
		overlay[i++] >>= 1;
	return (1);
}

int		shift_tet_overlay_far_left(t_u64b *overlay, int size)
{
	int	i;
	int	can_shift;

	can_shift = 1;
	while (can_shift)
	{
		i = 0;
		while (i < size)
		{
			if (overlay[i] & 0x8000000000000000)
			{
				can_shift = 0;
				break ;
			}
			i++;
		}
		if (can_shift)
		{
			i = 0;
			while (i < size)
				overlay[i++] <<= 1;
		}
	}
	return (1);
}

t_u64b	*push_tet_in_square(t_u64b *s, t_u16b b_tet, t_u64b *col_bounds, int *row_bounds)
{
	t_u64b	*tet_overlay;

	tet_overlay = (t_u64b *)malloc(sizeof(t_u64b) * 64);
	create_tet_overlay(tet_overlay, b_tet);
	while (overlays_overlap(s, tet_overlay, 64))
	{
		shift_tet_overlay_right(tet_overlay, 64);
		if (!(in_row_bounds(tet_overlay, *row_bounds, 64)))
		{
			create_tet_overlay(tet_overlay, b_tet);
			(*col_bounds) >>= 1;
			(*row_bounds)++;
		}
		if (!(in_col_bounds(tet_overlay, *col_bounds, 64)))
		{
			shift_tet_overlay_down(tet_overlay, 64);
			shift_tet_overlay_far_left(tet_overlay, 64);
		}
	}
	set_overlays(s, tet_overlay, 64);
	return (tet_overlay);
}*/

/*int		count_bits(t_u16b b)
{
	int	c;

	c = 0;
	while (b > 0)
	{
		if ((b & 0x0001) == 0x0001)
			c++;
		b = b >> 1;
	}
	return (c);
}*/
/*
int		find_next_open_bit(t_u64b s)
{
	t_u64b	start;
	int		pos;

	start = 0x1;
	pos = 1;
	while (!(s & start) && start != 0x8000000000000000)
	{
		start = start << 1;
		pos++;
	}
	if (start == 0x8000000000000000)
		pos++;
	return (pos - 1);
}*/
/*
void	set_overlays(t_u64b *o1, t_u64b *o2, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		o1[i] = o1[i] | o2[i];
		i++;
	}
}*/
