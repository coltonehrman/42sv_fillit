/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_invalids.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cehrman <cehrman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 18:58:25 by cehrman           #+#    #+#             */
/*   Updated: 2020/03/08 18:58:26 by cehrman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		check_invalid_tet(char *tet)
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
		return (0);
	return (1);
}

int		check_file_split(char **file_split)
{
	int i;

	i = 0;
	while (file_split[i])
	{
		if (ft_strlen(file_split[i]) != 16 || !check_invalid_tet(file_split[i]))
			return (0);
		++i;
	}
	return (1);
}
