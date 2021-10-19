/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 13:58:30 by thi-phng          #+#    #+#             */
/*   Updated: 2021/10/18 15:03:12 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
