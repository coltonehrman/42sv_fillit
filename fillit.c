/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cehrman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 14:08:06 by cehrman           #+#    #+#             */
/*   Updated: 2020/02/27 12:01:20 by cehrman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "fillit.h"

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

int		number_of_tets(char *tetriminos)
{
	char	**tets;
	int		i;
	
	// split on new line to get each individual tetrimino
	tets = ft_strsplit(tetriminos, '\n');
	i = 0;
	while (tets[i++])
		;
	// free memory from split
	free_matrix(&tets);
	return (i - 1);
}

t_ush		tet_to_bin(char *tet)
{
	t_ush	bin;
	int				x;

	//....|####|....|....
	//0000 1111 0000 0000
	bin = 0;
	x = 0x8000;
	while (*tet)
	{
		if (*tet == '#')
			bin += x;
		x = x >> 1;
		tet++;
	}
	return (bin);
}

int			left_most_bit(t_ull n)
{
	int pos;

	pos = 65;
	while (pos-- > 0)
	{
		// 0x8000 0000 0000 0000 is 64 bit binary with left most bit set to 1
		if (0x8000000000000000 & n)
			return (pos);
		n <<= 1;
	}
	return (-1);
}

void		print_bin(t_ull n, int size)
{
	int					i;
	int					prints;
	t_ull	x;

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
		if (prints == 4)
		{
			ft_putchar(' ');
			prints = 0;
		}
		x >>= 1;
	}
}

void		print_overlay(t_ull *overlay, int rows, int size)
{
	int	i;

	i = 0;
	while (i < rows)
	{
		print_bin(overlay[i++], size);
		ft_putchar('\n');
	}
	ft_putchar('\n');
}

void		print_overlays(t_ull *s, int s_size, t_ull **layers, t_ull col_b, int row_b)
{
	int	i;
	int j;
	int	printed_char;
	t_ull col;

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

int			count_bits(t_ush b)
{
	int c;

	//0000 1100 0100 0100
	c = 0;
	while (b > 0)
	{
		if ((b & 0x0001) == 0x0001)
			c++;
		b = b >> 1;
	}
	return (c);
}

int			get_size(int bit_count)
{
	int	size;

	size = 2;
	while ((size * size) <= bit_count)
		size++;
	return (size);
}

t_uch		get_row_of_tet(t_ush tet, int row)
{
	t_uch	nib;

	tet = tet << ((row - 1) * 4);
	tet = tet >> 12;
	nib = tet;
	return (nib);
}

t_ush		shift_to_corner(t_ush corner, t_ush tet)
{
	t_ush shifted;

	shifted = tet;

	while (!(shifted & corner))
		shifted = shifted << 1;
	return (shifted);
}

int			can_shift_tet(t_ush tet)
{
	t_uch row[4];

	row[0] = get_row_of_tet(tet, 1);
	row[1] = get_row_of_tet(tet, 2);
	row[2] = get_row_of_tet(tet, 3);
	row[3] = get_row_of_tet(tet, 4);

	// 0000 0011
	return (!(row[0] & 0x08) && !(row[1] & 0x08) &&
			!(row[2] & 0x08) && !(row[3] & 0x08));
}

t_ush		compress_tet(t_ush tet)
{
	t_ush	shifted;
	t_uch	row[4];
	int				i;

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

void		read_tets(int fd, char **tets)
{
	char	*line;
	char	*tmp;

	// parse each line
	while (get_next_line(fd, &line) > 0)
	{
		if (!(*line))
		{
			free(line);
			// new tetrimino incoming
			tmp = *tets;
			*tets = ft_strjoin(tmp, "\n");
			free(tmp);
		}
		else
		{
			tmp = *tets;
			*tets = ft_strjoin(tmp, line);
			free(line);
			free(tmp);
			tmp = 0;
		}
	}
}

void		init_overlay(t_ull *s, int size)
{
	while (size-- > 0)
		s[size] = 0x0;
}

int			find_next_open_bit(t_ull s)
{
	t_ull	start;
	int					pos;

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
}

void		create_tet_overlay(t_ull *overlay, t_ush b_tet)
{
	t_ull	row;
	int					i;

	init_overlay(overlay, 64);
	b_tet = compress_tet(b_tet);
	
	i = 0;
	while (i < 4)
	{
		row = 0x0;
		// return t_uch 0000 0000
		row = get_row_of_tet(b_tet, i + 1);
		// shift over to end of overlay
		row <<= 60;
		overlay[i++] = row;
	}
}

void		set_overlays(t_ull *o1, t_ull *o2, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		o1[i] = o1[i] | o2[i];
		i++;
	}
}

int			overlays_overlap(t_ull *o1, t_ull *o2, int size)
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

int			in_col_bounds(t_ull *overlay, t_ull col_bounds, int size)
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

int			in_row_bounds(t_ull *overlay, int row_bounds, int size)
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

int			in_bounds(t_ull *overlay, t_ull col_bounds, int row_bounds)
{
	return (in_col_bounds(overlay, col_bounds, 64)
			&& in_row_bounds(overlay, row_bounds, 64));
}

void		shift_tet_overlay_down(t_ull *overlay, int size)
{
	t_ull	prev;
	t_ull	curr;
	t_ull	next;
	int					i;
	
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
		i+= 3;
	}
}

int			shift_tet_overlay_right(t_ull *overlay, int size)
{
	int	i;

	i = 0;
	while (i < size)
		overlay[i++] >>= 1;
	return (1);
}

int			shift_tet_overlay_far_left(t_ull *overlay, int size)
{
	int i;
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
				break;
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

t_ull		*push_tet_in_square(t_ull *s, t_ush b_tet, t_ull *col_bounds, int *row_bounds)
{
	t_ull	*tet_overlay;

	tet_overlay = (t_ull *)malloc(sizeof(t_ull) * 64);
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
}

int			calc_min_square_size(int total_bits)
{
	int square;

	square = 2;
	while ((square * square) <= total_bits)
		square++;
	return (square - 1);
}

void		set_bounds(t_ull *col_bounds, int *row_bounds, int square)
{
	printf("square: %d\n", square);
	*col_bounds = (0xFFFFFFFFFFFFFFFF >> square);
	*row_bounds = square;
}

//int			solve_square(t_ull col_pos, int row_pos, t_ull **tet_overlays)

/***********************************************\ 
	
  solve_square(t_ull )


\***********************************************/

int			main(int argc, char **argv)
{
	t_ull	square[64];
	t_ull	col_bounds;
	t_ush	b_tet[10];  // size is hardcoded
	char	**matrix;
	char	*tets;
	int		row_bounds;
	int		fd;
	int		i;
	int		total_tets;
	int		total_bits;
	t_ull	**tet_overlays;

	if (argc < 1)
		return (0);
	tets = ft_strnew(0);
	// open file for reading
	if ((fd = open(argv[1], O_RDONLY)) > 0)
	{
		read_tets(fd, &tets);
		matrix = ft_strsplit(tets, '\n');
		free(tets);
		i = 0;
		total_bits = 0;
		while (matrix[i])
		{
			// converts tets to binary (t_ushs)
			b_tet[i] = tet_to_bin(matrix[i]);
			print_bin(b_tet[i], 16);
			ft_putchar('\n');
			total_bits += count_bits(b_tet[i]);
			i++;
		}
		free_matrix(&matrix);
		printf("\n");
		init_overlay(square, 64);
		set_bounds(&col_bounds, &row_bounds, calc_min_square_size(total_bits));
		total_tets = (total_bits / 4);
		tet_overlays = (t_ull **)malloc(sizeof(t_ull*) * (total_tets + 1));
		i = 0;
		while (i < total_tets)
		{
			tet_overlays[i] = push_tet_in_square(square, b_tet[i], &col_bounds, &row_bounds);
			i++;
		}
		tet_overlays[i] = 0;
		print_overlay(square, 10, 64);
		print_overlays(square, 64, tet_overlays, col_bounds, row_bounds);
	
		i = 0;
		while ((tet_overlays)[i])
		{
			free(((void *)((tet_overlays)[i])));
			tet_overlays[i] = 0;
			i++;
		}
		free(tet_overlays);
		tet_overlays = 0;
	}
	return (0);
}
