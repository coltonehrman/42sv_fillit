/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cehrman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 20:17:51 by cehrman           #+#    #+#             */
/*   Updated: 2020/02/19 20:21:16 by cehrman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*new_str;
	int		i;
	int		len;

	if (!s || !f)
		return (0);
	i = -1;
	len = ft_strlen(s);
	new_str = (char *)malloc(sizeof(char) * (len + 1));
	if (!new_str)
		return (0);
	while (++i < len)
		new_str[i] = f(i, s[i]);
	new_str[i] = 0;
	return (new_str);
}
