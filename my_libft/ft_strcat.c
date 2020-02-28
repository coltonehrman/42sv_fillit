/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cehrman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 10:23:10 by cehrman           #+#    #+#             */
/*   Updated: 2020/02/19 10:27:50 by cehrman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *s1, const char *s2)
{
	int	i;
	int	s1_len;
	int	s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	i = 0;
	while (i <= s2_len)
	{
		s1[s1_len] = s2[i];
		s1_len++;
		i++;
	}
	return (s1);
}
