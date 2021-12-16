/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   union.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 16:23:53 by thi-phng          #+#    #+#             */
/*   Updated: 2021/09/10 18:46:50 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	find_me(char c, char *str)
{
	int n;

	n = -1;
	while (str && str[(++n)])
	{
		if (str[n] == c)
			return (c);
	}
	return (0);
}

int	ft_union(char *str1, char *str2)
{
	int n = 0;
	int j = 0;
	char printed[1000];

	while (str1[n])
	{
		if (str1[n] && !(find_me(str1[n], printed)))
		{
			write(1, &str1[n], 1);
			printed[j] = str1[n];
			j++;
		}
		n++;
	}
	n = 0;
	while (str2[n])
	{
		if (str2[n] && !(find_me(str2[n], printed)))
		{
			write(1, &str2[n], 1);
			printed[j] = str2[n];
			j++;
		}
		n++;
	}
	printed[j] = '\0';
	write(1, "\n", 1);
	return (0);
}

int	main(int ac, char **av)
{
	if (ac == 3)
	{
		ft_union(av[1], av[2]);
	}
	else
		write(1, "\n", 1);
	return (0);
}
