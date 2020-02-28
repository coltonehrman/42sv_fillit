/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cehrman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 14:08:22 by cehrman           #+#    #+#             */
/*   Updated: 2020/02/28 14:30:26 by cehrman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H
# include <stdlib.h>
# include <fcntl.h>
# include "libft/libft.h"

typedef unsigned long long	t_u64b;
typedef unsigned short		t_u16b;
typedef unsigned char		t_u8b;

t_u16b  compress_tet(t_u16b tet);
t_u16b	tet_to_bin(char *tet);

void	set_bounds(t_u64b *col_bounds, int *row_bounds, int square);
void	add_bounds_to_square(t_u64b *s, int bounds);
void	read_tets(int fd, char **tets);
void	init_overlay(t_u64b *s, int size);
void	free_matrix(char ***matrix);


int		solve_square(int bounds, t_u64b *s, t_u16b *b_tets, int call);
int		calc_min_square_size(int total_bits);
int		get_num_strings(char **matrix);
int		count_bits(t_u16b b);

/* ***************** */
/*  DEBUG FUNCTIONS  */
/* ***************** */
void	print_bin(t_u64b n, int size);
void	print_overlay(t_u64b *overlay, int rows, int size);
#endif
