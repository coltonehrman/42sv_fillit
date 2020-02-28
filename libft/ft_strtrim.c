/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cehrman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 09:13:10 by cehrman           #+#    #+#             */
/*   Updated: 2020/02/20 10:01:59 by cehrman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char	*str;
	int		i[4];

	if (!s)
		return (0);
	i[0] = 0;
	i[1] = ft_strlen(s);
	i[2] = 0;
	i[3] = 0;
	while (ft_iswhitespace(s[i[0]++]))
		i[2]++;
	i[0] = i[1] - 1;
	if (i[2] != i[1])
		while (ft_iswhitespace(s[i[0]--]))
			i[3]++;
	str = (char *)malloc(sizeof(char) * (i[1] - (i[2] + i[3]) + 1));
	if (!str)
		return (0);
	i[0] = 0;
	s = s + i[2];
	while (i[0] < (i[1] - (i[2] + i[3])))
		str[i[0]++] = *(s++);
	str[i[0]] = 0;
	return (str);
}
