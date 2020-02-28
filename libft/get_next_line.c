/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cehrman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 11:22:47 by cehrman           #+#    #+#             */
/*   Updated: 2020/02/27 17:26:07 by cehrman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check_cache(char **cache, char **line)
{
	int		i;
	char	*data;
	char	*match;
	char	*rest;

	i = 0;
	data = *cache;
	while (data[i])
	{
		if (data[i] == '\n')
		{
			match = ft_strsub(data, 0, i);
			rest = ft_strsub(data, i + 1, ft_strlen(data) + 1);
			free(data);
			*cache = rest;
			*line = match;
			return (1);
		}
		i++;
	}
	return (0);
}

int	read_fd(int fd, char **cache)
{
	char	*tmp[2];
	char	*data;
	char	buff[BUFF_SIZE];
	int		bytes_read;

	bytes_read = 0;
	data = *cache;
	bytes_read = read(fd, &buff, BUFF_SIZE);
	if (bytes_read < 0)
		return (-1);
	if (bytes_read > 0)
	{
		tmp[0] = data;
		tmp[1] = ft_strsub(buff, 0, bytes_read);
		*cache = ft_strjoin(tmp[0], tmp[1]);
		free(tmp[0]);
		free(tmp[1]);
	}
	return (bytes_read);
}

int	get_next_line(int fd, char **line)
{
	static char	*cache[MAX_FD];
	int			bytes_read;

	if (fd < 0 || fd > MAX_FD || !line)
		return (-1);
	if (!cache[fd])
		cache[fd] = ft_strnew(0);
	if (check_cache(&(cache[fd]), line) == 1)
		return (1);
	if ((bytes_read = read_fd(fd, &(cache[fd]))) == -1)
		return (-1);
	else if (bytes_read == 0)
	{
		if (ft_strlen(cache[fd]) > 0)
		{
			*line = ft_strdup(cache[fd]);
			free(cache[fd]);
			cache[fd] = 0;
			return (1);
		}
		return (0);
	}
	return (get_next_line(fd, line));
}
