/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cehrman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 09:47:08 by cehrman           #+#    #+#             */
/*   Updated: 2020/02/19 09:54:25 by cehrman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	int		size;
	char	*dup;

	size = ft_strlen(s1);
	dup = (char *)malloc(sizeof(char) * (size + 1));
	if (!dup)
		return (0);
	i = 0;
	while (i <= size)
	{
		dup[i] = s1[i];
		i++;
	}
	return (dup);
}
