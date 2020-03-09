/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tet_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cehrman <cehrman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 01:23:49 by cehrman           #+#    #+#             */
/*   Updated: 2020/03/09 01:23:55 by cehrman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

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
