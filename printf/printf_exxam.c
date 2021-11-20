/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exam03.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 12:23:54 by thi-phng          #+#    #+#             */
/*   Updated: 2021/11/02 12:49:42 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct	s_type
{
	char			*s;
	long int		d;
	unsigned int	x;
	int				ret;
}				t_type;

void	init(t_type *p)
{
	p->s = 0;
	p->d = 0;
	p->x = 0;
	p->ret = 0;
}

int	ft_print_s(char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
	return (i);
}

void	put_d(int n)
{
	long int	l;
	char		c;

	l = n;
	if (l < 0)
	{
		write(1, "-", 1);
		l = -l;
	}
	if (l >= 10)
		put_d((int)l / 10);
	c = (l % 10) + '0';
	write(1, &c , 1);
}

int	size_d(int d)
{
	int	i;

	i = 1;
	printf("\n  Test bonne taille de %d" ,d);
	if (d < 0)
		i++;
	while (d / 10)
	{
		d /= 10;
		i++;
	}
	printf(": %d\n  " , i);
	return (i);
}

int	ft_print_d(int d)
{
	put_d(d);
	return (size_d(d));
}


void	put_x(unsigned int x)
{
	char	*base;

	base = "0123456789abcdef";
	if (x >= 16)
		put_d(x / 16);
	write(1, &base[(x % 16)], 1);
}

int	size_x(unsigned int x)
{
	int	i;

	i = 1;
	printf("\n  Test bonne taille de %d : " , x);
	while (x / 16)
	{
		x /= 16;
		i++;
	}
	printf("%d\n " , i);
	return (i);
}

int	ft_print_x(unsigned int x)
{
	put_x(x);
	return (size_x(x));
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
		p.d = va_arg(ap, int);
		p.ret += ft_print_d(p.d);
	}
	if (c == 'x')
	{
		p.x = va_arg(ap, unsigned int);
		p.ret += ft_print_x(p.x);
	}
	return (p.ret);
}

int	ft_printf(const char *s, ...)
{
	int		i;
	int		ret;
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
			ret += write(1, &s[i], 1);
		i++;
	}
	va_end(ap);
	return (ret);
}


int	main()
{
	int		n = 0;
	char *s = "hello coucou";
	unsigned int x = 16;

	printf("%d\n", ft_printf("Tho oi %s cac em %d tuoi, and %x\n", s, n, x));
	printf("%d\n", printf("Tho oi %s cac em %d tuoi, and %x\n", s, n, x));
	printf("%d\n", ft_printf("%s\n", s));
	printf("%d\n", printf("%s\n", s));
	return (0);
}
