/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cehrman <cehrman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 14:20:37 by cehrman           #+#    #+#             */
/*   Updated: 2020/03/08 20:44:29 by cehrman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		read_file(char *file, char **data)
{
	char	*line;
	char	*tmp;
	int		fd;
	int		res;

	if ((fd = open(file, O_RDONLY)) < 0)
		return (0);
	while ((res = get_next_line(fd, &line) > 0))
	{
		if (!(*line))
		{
			tmp = *data;
			*data = ft_strjoin(tmp, "\n");
		}
		else
		{
			tmp = *data;
			*data = ft_strjoin(tmp, line);
		}
		ft_strdel(&line);
		ft_strdel(&tmp);
	}
	return ((res == -1) ? -1 : 1);
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

t_tet	*create_tet(char *tet_str, char c)
{
	t_tet	*tet;

	tet = (t_tet *)malloc(sizeof(t_tet));
	tet->data = tet_to_bin(tet_str);
	tet->col = -1;
	tet->row = -1;
	tet->c = c;
	return (tet);
}

t_tet	**parse_file_data(char **file_data, int *total_bits)
{
	t_tet	**tets;
	char	**file_split;
	char	c;
	int		i;

	file_split = ft_strsplit(*file_data, '\n');
	ft_strdel(file_data);
	if (!check_file_split(file_split))
		return (0);
	if (!(tets = (t_tet **)malloc(sizeof(t_tet *) *
				(get_num_strings(file_split) + 1))))
		return (0);
	i = 0;
	c = 'A';
	*total_bits = 0;
	while (file_split[i])
	{
		tets[i] = create_tet(file_split[i], c++);
		++i;
	}
	tets[i] = 0;
	free_matrix(&file_split);
	return (tets);
}

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
	if (!(tets = parse_file_data(&file_data, &total_bits)))
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
