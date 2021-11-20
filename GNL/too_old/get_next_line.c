/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 13:57:17 by thi-phng          #+#    #+#             */
/*   Updated: 2021/10/19 14:16:49 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*return_value(char **overflow)
{
	char	*line;
	char	*tmp;
	const	int	pos = strclen(*overflow, $ENDL);
	
	line = NULL;
	if (pos != $NOT_FOUND)
	{
		line = ft_strndup(*overflow, pos + 1);
		tmp = *overflow;
		*overflow = ft_strndup(*overflow + pos + 1,
			strclen(*overflow + pos + 1, $ZERO));
		free(tmp);
	}
	if (*overflow)
	{
		line = ft_strndup(*overflow, strclen(*overflow, $ZERO));
		free(*overflow);
		*overflow = NULL;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char		*overflow;
	char			buff[BUFFER_SIZE + 1];
	int				ret;

	while (strclen(overflow, $ENDL) == $NOT_FOUND)
	{
		ret = read(fd, &buff, BUFFER_SIZE);
		if (ret <= 0)
			break ;
		buff[ret] = $ZERO;
		if (!overflow)
			overflow = ft_strndup(buff, strclen(buff, $ZERO));
		else
			overflow = ft_strjoin(overflow, buff);
	}
	return (return_value(&overflow));
}
/*
int	main(int argc, char **argv)
{
	int		fd;
	char	*line;

	if (argc != 2)
	{
		printf("argc!\n");
		exit (0);
	}
	fd = open(argv[1], O_RDONLY);
	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}
	return (0);
}*/
