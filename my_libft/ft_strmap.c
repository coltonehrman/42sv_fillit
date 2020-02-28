/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cehrman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 19:50:15 by cehrman           #+#    #+#             */
/*   Updated: 2020/02/19 20:17:12 by cehrman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
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
		new_str[i] = f(s[i]);
	new_str[i] = 0;
	return (new_str);
}
