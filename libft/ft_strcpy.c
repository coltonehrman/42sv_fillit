/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cehrman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 09:53:57 by cehrman           #+#    #+#             */
/*   Updated: 2020/02/19 09:57:08 by cehrman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpy(char *dst, const char *src)
{
	int		src_len;
	int		i;

	i = 0;
	src_len = ft_strlen(src);
	while (i <= src_len)
	{
		dst[i] = src[i];
		i++;
	}
	return (dst);
}
