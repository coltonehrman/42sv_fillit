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
