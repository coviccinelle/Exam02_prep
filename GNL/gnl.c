
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#define $NOT_FOUND -1
#define $ENDL '\n'
#define $ZERO '\0'

int	strclen(char *str, char c)
{
	int	i;

	i = 0;
	if (!str)
		return ($NOT_FOUND);
	if (c == $ZERO)
	{
		while (str[i])
			i++;
		return (i);
	}
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return ($NOT_FOUND);
}

char	*ft_strndup(char *str, int n)
{
	char	*ret;
	int		i;

	i = 0;
	while (str[i] && i < n)
		i++;
	ret = malloc(sizeof(char) * i + 1);
	if (!ret)
		return (NULL);
	i = -1;
	while (str[++i] && i < n)
		ret[i] = str[i];
	ret[i] = $ZERO;
	return (ret);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*ret;
	int		size;
	int		i;
	int		y;

	i = 0;
	y = 0;
	if (!s1 || !s2)
		return (NULL);
	size = strclen(s1, $ZERO) + strclen(s2, $ZERO) + 1;
	ret = malloc(sizeof(char) * size);
	if (!ret)
		return (NULL);
	while (s1[i])
	{
		ret[i] = s1[i];
		i++;
	}
	while (s2[y])
	{
		ret[i + y] = s2[y];
		y++;
	}
	ret[i + y] = $ZERO;
	free(s1);
	return (ret);
}

char	*return_value(char **overflow)
{
	char	*line;
	char	*tmp;
	const	int	pos = strclen(*overflow, $ENDL);

	if (pos != $NOT_FOUND)
	{
		line = ft_strndup(*overflow, pos + 1);
		tmp = *overflow;
		*overflow = ft_strndup(*overflow + pos + 1,
		strclen(*overflow + pos + 1, $ZERO));
		free(tmp);
	}
	else if (*overflow)
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
}
