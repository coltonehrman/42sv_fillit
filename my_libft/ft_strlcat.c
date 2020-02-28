/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cehrman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 11:41:17 by cehrman           #+#    #+#             */
/*   Updated: 2020/02/21 10:55:29 by cehrman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>
#include <stdio.h>

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	int	i;
	int	dst_len;
	int	src_len;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	i = 0;
	if ((int)dstsize <= dst_len)
		src_len += dstsize;
	else
		src_len += dst_len;
	while (src[i] && dst_len + 1 < (int)dstsize)
	{
		dst[dst_len] = src[i];
		dst_len++;
		i++;
	}
	dst[dst_len] = 0;
	return (src_len);
}
