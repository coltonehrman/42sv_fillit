#include "fillit.h"

void	print_bin(t_u64b n, int size)
{
	int					i;
	int					prints;
	t_u64b	x;

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
		if (prints == 4 && i != 0)
		{
			ft_putchar(' ');
			prints = 0;
		}
		x >>= 1;
	}
}

void	print_overlay(t_u64b *overlay, int rows, int size)
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
