/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cehrman <cehrman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 01:20:16 by cehrman           #+#    #+#             */
/*   Updated: 2020/03/09 01:32:29 by cehrman          ###   ########.fr       */
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

t_tet	**parse_file_data(char **file_data, int *total_bits)
{
	t_tet	**tets;
	char	**file_split;
	char	c;
	int		i;

	file_split = ft_strsplit(*file_data, '\n');
	if (!check_valid_file_split(file_split))
		return (0);
	if (!(tets = (t_tet **)malloc(sizeof(t_tet *) *
				(get_num_strings(file_split) + 1))))
		return (0);
	i = 0;
	c = 'A';
	while (file_split[i])
	{
		tets[i] = create_tet(file_split[i], c++);
		++i;
	}
	*total_bits = i * 4;
	tets[i] = 0;
	free_matrix(&file_split);
	return (tets);
}
