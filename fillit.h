/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cehrman <cehrman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 14:08:22 by cehrman           #+#    #+#             */
/*   Updated: 2020/03/09 02:50:55 by cehrman          ###   ########.fr       */
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

/*
**	Tetrimino Struct
**	stores data in an
**	(unsigned short which is 16 bits long)
*/

typedef struct				s_tetrimino {
	t_u16b		data;
	int			col;
	int			row;
	char		c;
	int			szx;
	int			szy;
}							t_tet;

/*
**	FILE FUNCTIONS
*/

int							read_file(char *file, char **data);
t_tet						**parse_file_data(char **file_data, int *total_bits);

/*
**	TETRIMINO FUNCTIONS
*/


int							all_tets_placed(t_tet **b_tets);
t_tet						*create_tet(char *tet_str, char c);

/*
**	CHECK INVALID DATA
*/

int							check_invalid_tet_shape(char *tet);
int							check_invalid_tet_data(char *tet);
int							check_valid_file_split(char **file_split);

t_u64b						create_btet_row(int col, int row, t_u16b b_tet);
t_u16b						create_section(int col, int row, t_u64b *s);
t_u16b						compress_tet(t_u16b tet);
t_u16b						tet_to_bin(char *tet);

void						print_solution(t_u64b *square,
								t_tet **b_tets, int bounds);
void						add_bounds_to_square(t_u64b *s, int bounds);
void						place_tet(int col, int row, t_u64b *s,
								t_tet *b_tet);
void						unplace_tet(t_u64b *s, t_tet *b_tet);
void						init_overlay(t_u64b *s, int size);
void						free_matrix(char ***matrix);

int							solve_square(int bounds, t_u64b *s,
								t_tet **b_tets, t_tet **all_tets);
int							can_place_tet(int col, int row, t_u64b *s,
								t_u16b b_tet);
int							calc_min_square_size(int total_bits);
int							read_file(char *file, char **data);
int							get_num_strings(char **matrix);
int							count_b_tets(t_tet **b_tets);
int							count_bits(t_u16b b);

/*
**  DEBUG FUNCTIONS
*/
void						print_bin(t_u64b n, int bounds, int size);
void						print_overlay(t_u64b *overlay, int rows,
								int bounds, int size);
#endif
