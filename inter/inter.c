/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 10:46:02 by thi-phng          #+#    #+#             */
/*   Updated: 2021/10/18 10:46:06 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <unistd.h>

char	find_me(char c, const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (c);
		i++;
	}
	return (0);
}

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (0);
}

int	inter(char *str1, char *str2)
{
	int	n = 0;
	int j = 0;
	char	printed[256];

	while (str1[n])
	{
		if (find_me(str1[n], str2) && !(find_me(str1[n], printed)))
		{
			ft_putchar(str1[n]);
			printed[j] = str1[n];
			j++;
		}
		n++;
	}
	ft_putchar('\n');
	return (0);
}


int	main(int ac, char **av)
{
	if (ac == 3)
	{
		inter(av[1], av[2]);
		return (0);
	}
	return ('\n');
}
