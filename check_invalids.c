/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_invalids.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cehrman <cehrman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 18:58:25 by cehrman           #+#    #+#             */
/*   Updated: 2020/03/09 02:09:54 by cehrman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include "stdio.h"

int		another_point_touches(char *tet, int col, int row)
{
	int	top;
	int	left;
	int	right;
	int	bottom;

	top = col + ((row - 1) * 4);
	left = (col - 1) + (row * 4);
	right = (col + 1) + (row * 4);
	bottom = col + ((row + 1) * 4);
	if (row > 0 && tet[top] == '#')
		return (1);
	if (col > 0 && tet[left] == '#')
		return (1);
	if (col < 3 && tet[right] == '#')
		return (1);
	if (row < 3 && tet[bottom] == '#')
		return (1);
	return (0);
}

int		check_invalid_tet_shape(char *tet)
{
	int	i;
	int col;
	int row;

	i = 0;
	col = -1;
	row = 0;
	while (tet[i])
	{
		++col;
		if (col == 4)
		{
			col = 0;
			++row;
		}
		if (tet[i] == '#' && !another_point_touches(tet, col, row))
			return (1);
		++i;
	}
	return (0);
}

int		check_invalid_tet_data(char *tet)
{
	int	i;
	int	total_hashes;
	int	total_dots;

	i = 0;
	total_hashes = 0;
	total_dots = 0;
	while (tet[i])
	{
		if (tet[i] == '#')
			++total_hashes;
		else if (tet[i] == '.')
			++total_dots;
		++i;
	}
	if (total_hashes != 4 || total_dots != 12)
		return (1);
	return (0);
}

int		check_valid_file_split(char **file_split)
{
	int i;

	i = 0;
	while (file_split[i])
	{
		if (ft_strlen(file_split[i]) != 16 ||
			check_invalid_tet_data(file_split[i]) ||
			check_invalid_tet_shape(file_split[i]))
			return (0);
		++i;
	}
	return (1);
}
