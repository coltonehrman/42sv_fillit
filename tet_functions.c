/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tet_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cehrman <cehrman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 01:23:49 by cehrman           #+#    #+#             */
/*   Updated: 2020/03/09 02:50:41 by cehrman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		all_tets_placed(t_tet **b_tets)
{
	while (*b_tets)
	{
		if ((*b_tets)->col == -1 || (*b_tets)->row == -1)
			return (0);
		++b_tets;
	}
	return (1);
}

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

int		count_x(t_u16b data)
{
	int tmp;
	int out;
	int i;

	out = 1;
	i = -1;
	tmp = 0;
	while (++i < 16)
	{
		if ((i & 3) == 0)
			tmp = 0;
		if (data & 0x8000)
			tmp++;
		data = data << 1;
		if (tmp > out)
			out = tmp;
	}
	return (out);
}

int		count_y(t_u16b data)
{
	int i;

	i = 0;
	while (++i <= 4)
	{
		data = data << 4;
		if (data == 0)
			break ;
	}
	return (i);
}

t_tet	*create_tet(char *tet_str, char c)
{
	t_tet	*tet;

	tet = (t_tet *)malloc(sizeof(t_tet));
	tet->data = tet_to_bin(tet_str);
	tet->szx = count_x(tet->data);
	tet->szy = count_y(tet->data);
	tet->col = -1;
	tet->row = -1;
	tet->c = c;
	return (tet);
}
