/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cehrman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 16:18:04 by cehrman           #+#    #+#             */
/*   Updated: 2020/02/20 12:04:59 by cehrman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*c_dst;
	const char	*c_src;
	size_t		i;

	i = 0;
	c_dst = dst;
	c_src = src;
	if (!dst && !src)
		return (dst);
	if (c_src < c_dst)
		while (i++ < len)
			c_dst[len - i] = c_src[len - i];
	else
	{
		while (len-- > 0)
		{
			*c_dst = *c_src;
			c_dst++;
			c_src++;
		}
	}
	return (dst);
}
