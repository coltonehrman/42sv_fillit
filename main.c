/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cehrman <cehrman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 14:20:37 by cehrman           #+#    #+#             */
/*   Updated: 2020/03/09 02:06:01 by cehrman          ###   ########.fr       */
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

/*
**	1) read from file
**		+ invalid checks
**	2) parse data from file into tet structs
**		+ invalid check
**	3) initialize square overlay
**	4) caluclate square size based off total tets
*/

int		main(int argc, char **argv)
{
	int		bounds;
	int		total_bits;
	char	*file_data;
	t_tet	**tets;
	t_u64b	square[64];

	if (argc != 2)
		return (0);
	file_data = ft_strnew(0);
	if (!read_file(argv[1], &file_data) ||
		file_data[ft_strlen(file_data) - 1] == '\n')
		return (write(1, "error\n", 6));
	if (!(tets = parse_file_data(&file_data, &total_bits))
		|| all_tets_placed(tets))
		return (write(1, "error\n", 6));
	init_overlay(square, 64);
	bounds = calc_min_square_size(total_bits);
	add_bounds_to_square(square, bounds);
	while (!solve_square(bounds, square, tets, 1) || !all_tets_placed(tets))
	{
		++bounds;
		init_overlay(square, 64);
		add_bounds_to_square(square, bounds);
	}
	print_solution(square, tets, bounds);
	return (0);
}
