/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   training_putnbr_x.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 12:45:27 by thi-phng          #+#    #+#             */
/*   Updated: 2021/10/19 15:22:50 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>

typedef struct	s_type
{
	char			*s;
	unsigned int	x;
	long int		d;
	int				ret;
}				t_type;


int	put_nbr(long int n)
{
	char	c;

	if (n < 0)
	{
		n = -n;
		write(1, "-", 1);
	}
	if (n / 10)
		put_nbr(n / 10);
	c = n % 10 + '0';
	write(1, &c, 1);
	return (0);
}

int	size_d(long int n)
{
	int	i;

	i = 1;
	if (n < 0)
		i++;
	while (n / 10)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

int	put_x(unsigned int x)
{
	char	c;
	char	*str;

	str = "0123456789abcdef";
	if (x / 16)
		put_x(x / 16);
	c = str[(x % 16)];
	write(1, &c, 1);
	return (0);
}

int	size_x(unsigned int x)
{
	int	ret;

	ret = 1;
	while (x / 16)
	{
		x /= 16;
		ret++;
	}
	return (ret);
}

int	ft_print_s(char *str)
{
	int	ret;

	ret = 0;
	while (str[ret])
	{
		ret += write(1, &str[ret], 1);
	}
	return (ret);
}

void	init(t_type *p)
{
	p->s = 0;
	p->x = 0;
	p->d = 0;
	p->ret = 0;
}

int	ft_stock(char c, va_list ap)
{
	t_type p;
	init(&p);

	if (c == 's')
	{
		p.s = va_arg(ap, char *);
		p.ret += ft_print_s(p.s);
	}
	if (c == 'd')
	{
		p.d = va_arg(ap, long int);
		p.ret += size_d(p.d);
		put_nbr(p.d);
	}
	if (c == 'x')
	{
		p.x = va_arg(ap, unsigned int);
		p.ret += size_x(p.x);
		put_x(p.x);
	}
	return (p.ret);
}

int	ft_printf(char *s, ...)
{
	int		ret;
	int		i;
	va_list	ap;

	i = 0;
	ret = 0;
	va_start(ap, s);
	while (s[i])
	{
		if (s[i] == '%')
		{
			i++;
			ret += ft_stock(s[i], ap);
		}
		else if (s[i] != '%')
		{
			write(1, &s[i], 1);
			ret++;
		}
		i++;
	}
	va_end(ap);
	return (ret);
}

int	main()
{
	int		n = 376283;
	char *s = "hello coucou";
	unsigned int x = 43;

	printf("%d\n", ft_printf("Tho oi %s cac em %d tuoi, and %x\n", s, n, x));
	printf("%d\n", printf("Tho oi %s cac em %d tuoi, and %x\n", s, n, x));
	ft_printf("Tho oi %s cac em %d tuoi, and %x\n", s, n, x);
	printf("Tho oi %s cac em %d tuoi, and %x\n", s, n, x);
	return (0);
}
