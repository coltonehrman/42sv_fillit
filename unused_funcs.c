#include "fillit.h"

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

int		left_most_bit(t_u64b n)
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
	int	i;
	int j;
	int	printed_char;
	t_u64b col;

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
