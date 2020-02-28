/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cehrman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 14:20:37 by cehrman           #+#    #+#             */
/*   Updated: 2020/02/28 14:20:55 by cehrman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int	main(int argc, char **argv)
{
	t_u64b	square[64];
	t_u64b	col_bounds;
	t_u16b	*b_tets;
	char	**tets_matrix;
	char	*tets_string;
	int		row_bounds;
	int		fd;
	int		i;
	int		total_tets;
	int		total_bits;

	if (argc != 2)
		return (0);
	tets_string = ft_strnew(0);
	// open file for reading
	if ((fd = open(argv[1], O_RDONLY)) > 0)
	{
		read_tets(fd, &tets_string);
		tets_matrix = ft_strsplit(tets_string, '\n');
		free(tets_string);
		total_bits = 0;
		b_tets = (t_u16b *)malloc(sizeof(t_u16b) * (get_num_strings(tets_matrix) + 1));

		i = 0;
		while (tets_matrix[i])
		{
			b_tets[i] = tet_to_bin(tets_matrix[i]);
			print_bin(b_tets[i], 16);
			ft_putchar('\n');
			total_bits += count_bits(b_tets[i]);
			++i;
		}
		b_tets[i] = 0;
		free_matrix(&tets_matrix);
		ft_putchar('\n');

		init_overlay(square, 64);
		set_bounds(&col_bounds, &row_bounds, calc_min_square_size(total_bits));
		total_tets = (total_bits / 4);
		add_bounds_to_square(square, row_bounds);
		while (!solve_square(row_bounds, square, b_tets, 1))
		{
			++row_bounds;
			++col_bounds;
			init_overlay(square, 64);
			add_bounds_to_square(square, row_bounds);
		}
		
		print_overlay(square, 10, 64);
	}
	return (0);
}
