/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cehrman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 14:08:06 by cehrman           #+#    #+#             */
/*   Updated: 2020/02/24 08:26:28 by cehrman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "fillit.h"

void			free_matrix(char ***matrix)
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

int				number_of_tets(char *tetriminos)
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

unsigned short	convert_tet_to_bin(char *tet)
{
	unsigned short	bin;
	int				x;

	//....|####|....|....
	//0000 1111 0000 0000
	bin = 0;
	x = 0x8000;
	while (*tet)
	{
		if (*tet == TET_SPACER_C)
		{
			tet++;
			continue;
		}
		if (*tet == '#')
			bin += x;
		x = x >> 1;
		tet++;
	}
	return (bin);
}

int				left_most_bit(unsigned long long n)
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

void			print_bin(unsigned long long n, int spacer)
{
	int					left_bit;
	int					prints;
	unsigned long long	x;

	x = 0x1;
	left_bit = left_most_bit(n);
	while (left_bit--)
		x <<= 1;
	x <<= 1;
	prints = 0;
	while (x)
	{
		prints++;
		if (x & n)
			ft_putnbr(1);
		else
			ft_putnbr(0);
		if (prints == spacer)
		{
			ft_putchar(' ');
			prints = 0;
		}
		x >>= 1;
	}
}

int				count_bits(unsigned short b)
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

int				get_size(int bit_count)
{
	int	size;

	size = 2;
	while ((size * size) <= bit_count)
		size++;
	return (size);
}

unsigned short	shift_to_corner(unsigned short corner, unsigned short tet)
{
	unsigned short shifted;

	shifted = tet;
	while ((shifted & corner) != corner)
		shifted = shifted << 1;
	return (shifted);
}

int				main(int argc, char **argv)
{
	char			**matrix;
	char			*tetriminos;
	char			*line;
	char			*tmp;
	unsigned short	b_tet[4];
	int				fd;
	int				bit_count;

	if (argc < 1)
		return (0);
	// set tetrimonos to something at first befor parsing
	tetriminos = ft_strnew(0);
	// open file for reading
	if ((fd = open(argv[1], O_RDONLY)) > 0)
	{
		// parse each line
		while (get_next_line(fd, &line) > 0)
		{
			// this condition runs essentially when it is an empty newline
			// because get_next_line parses on newlines
			if (!(*line))
			{
				// new tetrimino incoming
				tmp = tetriminos;
				tetriminos = ft_strjoin(tmp, "\n");
				free(tmp);
			}
			else
			{
				// parse tetrimino
				tmp = tetriminos;
				tetriminos = ft_strjoin(tmp, line);
				free(tmp);
				tmp = 0;
				// add "|" to separate lines
				tmp = tetriminos;
				// we space out each line of the tetrimino with a "|"
				tetriminos = ft_strjoin(tmp, TET_SPACER_S);
				free(tmp);
				tmp = 0;
			}
		}
		//printf("%d\n", number_of_tets(tetriminos));

		// create a matrix that splits each tet
		matrix = ft_strsplit(tetriminos, '\n');

		int i = 0;
		int size = 2;
		int square = 0x8;
		bit_count = 0;

		square = square << ((size * 2) + 1);
		//printf("%i\n", square);
		
		size++;
		square = square << ((size * 2) + 1);
		//printf("%i\n", square);

		while (matrix[i])
		{
			// converts tets to binary (unsigned shorts)
			b_tet[i] = convert_tet_to_bin(matrix[i]);
			print_bin(b_tet[i], 4);

			//printf("b_tet[%d] shifted: %u\n", i, shift_to_corner(0x8000, b_tet[i]));

			// count each bit ("#") to find out max size of solution square
			bit_count += count_bits(b_tet[i]);
			i++;
		}
	}
	return (0);
}
