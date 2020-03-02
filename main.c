/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cehrman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 14:20:37 by cehrman           #+#    #+#             */
/*   Updated: 2020/03/01 16:31:55 by cehrman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		read_file(char *file, char **data)
{
	char	*line;
	char	*tmp;
	int		fd;

	if ((fd = open(file, O_RDONLY)) <= 0)
		return (0);
	while (get_next_line(fd, &line) > 0)
	{
		if (!(*line))
		{
			free(line);
			tmp = *data;
			*data = ft_strjoin(tmp, "\n");
			free(tmp);
		}
		else
		{
			tmp = *data;
			*data = ft_strjoin(tmp, line);
			free(line);
			free(tmp);
			tmp = 0;
		}
	}
	return (1);
}

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

t_tet	**parse_file_data(char **file_data, int *total_bits)
{
	t_tet	**tets;
	char	**file_split;
	char	c;
	int		i;

	file_split = ft_strsplit(*file_data, '\n');
	ft_memdel((void **)file_data);
	if (!(tets = (t_tet **)malloc(sizeof(t_tet *) *
					(get_num_strings(file_split) + 1))))
		return (0);
	i = 0;
	c = 'A';
	*total_bits = 0;
	while (file_split[i])
	{
		tets[i] = (t_tet *)malloc(sizeof(t_tet));
		tets[i]->data = tet_to_bin(file_split[i]);
		*total_bits += count_bits(tets[i]->data);
		tets[i]->col = -1;
		tets[i]->row = -1;
		tets[i++]->c = c++;
	}
	tets[i] = 0;
	free_matrix(&file_split);
	return (tets);
}

int		main(int argc, char **argv)
{
	t_u64b	square[64];
	t_u64b	col_bounds;
	t_tet	**tets;
	char	*file_data;
	int		row_bounds;
	int		total_tets;
	int		total_bits;

	if (argc != 2)
		return (0);
	file_data = ft_strnew(0);
	if (!read_file(argv[1], &file_data))
		return (1);
	tets = parse_file_data(&file_data, &total_bits);
	init_overlay(square, 64);
	set_bounds(&col_bounds, &row_bounds, calc_min_square_size(total_bits));
	total_tets = (total_bits / 4);
	add_bounds_to_square(square, row_bounds);
	while (!solve_square(row_bounds, square, tets, 1) || !all_tets_placed(tets))
	{
		++row_bounds;
		++col_bounds;
		init_overlay(square, 64);
		add_bounds_to_square(square, row_bounds);
	}
	print_solution(square, tets, row_bounds);
	return (0);
}
