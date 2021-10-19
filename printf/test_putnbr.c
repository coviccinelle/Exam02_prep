/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_putnbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 12:05:08 by thi-phng          #+#    #+#             */
/*   Updated: 2021/10/19 12:45:10 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>


int	ft_putnbr(long int n)
{
	int		ret;
	char	c;

	ret = 0;
	if (n < 0)
	{
		n = -n;
		ret += write(1, "-", 1);
	}
	if (n / 10)
		ret += ft_putnbr(n/10);
	c = n % 10 + '0';
	ret += write(1, &c, 1);
	return (ret);
}

void    ft_putnbr_hexa(unsigned int n)
{
    char    *str;
    int     a;
    str = "0123456789abcdef";
    if (n / 16)
        ft_putnbr_hexa(n / 16);
    a = str[(n % 16)];
    write(1, &a, 1);
}

#include <stdio.h>
int	main()
{
	int	n = 997;
	unsigned int	x = 23;
	ft_putnbr(n);
	printf("\n");
	printf("%x\n", x);
	ft_putnbr_hexa(x);
	return (0);
}
