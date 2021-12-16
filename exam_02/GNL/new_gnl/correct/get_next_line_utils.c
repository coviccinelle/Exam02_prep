/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 12:53:32 by thi-phng          #+#    #+#             */
/*   Updated: 2021/10/29 14:57:42 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *str)
{
	size_t	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strchr(char *str, int c)
{
	size_t i = 0;
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
	char	*ret;
	size_t	i = 0, e = 0;
	if (!s1)
	{
		s1 = malloc(1);
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
//	if (!s2)
//		return (NULL);
	ret = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!ret)
		return (NULL);
	while (s1[i])
	{
		ret[i] = s1[i];
		i++;
	}
	while (s2[e])
	{
		ret[i] = s2[e];
		e++;
		i++;
	}
	ret[i] = '\0';
	free(s1);
	return (ret);
}

