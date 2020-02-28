/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cehrman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 13:53:01 by cehrman           #+#    #+#             */
/*   Updated: 2020/02/21 12:11:17 by cehrman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int	i;
	int n_len;

	if (!(*needle))
		return ((char *)haystack);
	i = 0;
	n_len = ft_strlen(needle);
	while (i < (int)len && *haystack)
	{
		if ((i + n_len) > (int)len)
			return (0);
		if (ft_strmatch((char *)haystack, (char *)needle))
			return ((char *)haystack);
		haystack++;
		i++;
	}
	return (0);
}
