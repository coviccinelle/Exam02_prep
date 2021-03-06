/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 15:00:34 by thi-phng          #+#    #+#             */
/*   Updated: 2021/10/30 10:30:02 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int	ft_strlen(char *str)
{
	int	i = 0;
	 while (str[i])
		 i++;
	 return (i);
}

char	*ft_strchr(char *str, char c)
{
	int	i = 0;

	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == c)
			return (&str[i]);
		i++;
	}
	return (NULL);
}


char	*ft_strjoin(char *s1, char *s2)
{
	int	i = 0;
	int	j = 0;
	char	 *ret;

	if (!s1)
	{
		s1 = malloc(1);
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	if (!s2)
		return (NULL);
	ret = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!ret)
		return (NULL);
	while (s1[i])
	{
		ret[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		ret[i + j] = s2[j];
		j++;
	}
	ret[i + j] = '\0';
	free(s1);
	return (ret);
}


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
	int		i = 0;

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
	return(ret);
}

char	*ft_stat(char *stat)
{
	int		i = 0;
	int		e = 0;
	char	*ret;

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
	char			*line;
	static char		*stat;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	stat = ft_read(fd, stat);
//	printf("stat = ft_read => %s\n", stat);
	if (!stat)
		return (NULL);
	line = get_line(stat);
//	printf("line = get_line => %s\n", line);
	stat = ft_stat(stat);
//	printf("stat = ft_stat => %s\n", stat);
	return (line);
}





int	main(int ac, char **av)
{
	int		fd;
	char	*line;

	if (ac != 2)
	{
		printf("ac !\n");
		exit (0);
	}
	fd = open(av[1], O_RDONLY);
	while ((line = get_next_line(fd)))
	{
		printf("%s\n", line);
		free(line);
	}
	return (0);
}
