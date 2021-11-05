/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 11:00:16 by thi-phng          #+#    #+#             */
/*   Updated: 2021/11/05 11:41:37 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read(int fd, char *stat)
{
	int		ret = 1;
	char	buf[BUFFER_SIZE + 1];

	while (ret != 0 && !ft_strchr(stat, '\n'))
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret == -1)
			return (NULL);
		buf[ret] = '\0';
		stat = ft_strjoin(stat, buf);
	}
	return (stat);
}

char	*get_line(char *stat)
{
	char	*ret;
	size_t	i = 0;

	if (!stat[0])
		return (NULL);
	ret = malloc(ft_strlen(stat) + 2);
	if (!ret)
		return (NULL);
	while (stat[i] && stat[i] != '\n')
	{
		ret[i] = stat[i];
		i++;
	}
	if (stat[i] == '\n')
	{
		ret[i] = '\n';
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

char	*ft_stat(char *stat)
{
	char	*ret;
	int		i = 0;
	int		e = 0;

	while (stat[i] && stat[i] != '\n')
		i++;
	if (!stat[i])
	{
		free(stat);
		return (NULL);
	}
	ret = malloc(ft_strlen(stat) - i + 1);
	if (!ret)
		return (NULL);
	i++;
	while (stat[i])
	{
		ret[e] = stat[i];
		i++;
		e++;
	}
	ret[e] = '\0';
	free(stat);
	return (ret);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stat;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	stat = ft_read(fd, stat);
	if (!stat)
		return (NULL);
	line = get_line(stat);
	stat = ft_stat(stat);
	return (line);
}
