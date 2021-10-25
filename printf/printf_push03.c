/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_push03.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 14:53:11 by thi-phng          #+#    #+#             */
/*   Updated: 2021/10/25 17:29:49 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

typedef struct	s_type
{
	char			*s;
	unsigned int	x;
	long int		n;
	int				ret;
}				t_type;


int	ft_print_s(const char *str)
{
	int	i;
	int	ret;

	ret = 0;
	i = 0;
	while (str[i])
	{
		ret += write(1, &str[i], 1);
		i++;
	}
	return(ret);
}

void	put_x(unsigned int x)
{
	char *base;

	base = "0123456789abcdef";
	if (x >= 16)
		put_x(x / 16);
	write(1, &base[(x % 16)], 1);
}

int	ft_size(unsigned int x)
{
	int	i;

	i = 0;
	while (x)
	{
		x /= 10;
		i++;
	}
	return (i);
}

int	ft_print_x(unsigned int x)
{
	int	ret;

	put_x(x);
	ret = ft_size(x);
	return (ret);
}


void	put_nbr(long int n)
{
	char	*base;

	base = "0123456789";
	if (n < 0)
	{
		write(1, "-", 1);
		n = -n;
	}
	if (n >= 10)
		put_nbr(n / 10);
	write(1, &base[(n % 10)], 1);
}


int	ft_size_d(long int n)
{
	int	i;

	i = 0;
	if (n < 0)
		i++;
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

int	ft_print_d(long int n)
{
	int	ret;

	put_nbr(n);
	ret = ft_size_d(n);
	return (ret);
}

void	init(t_type *p)
{
	p->s = 0;
	p->x = 0;
	p->n = 0;
	p->ret = 0;
}

int	ft_stock(char c, va_list ap)
{
	t_type	p;

	init(&p);
	if (c == 'x')
	{
		p.x = va_arg(ap, unsigned int);
		p.ret += ft_print_x(p.x);
	}
	if (c == 's')
	{
		p.s = va_arg(ap, char *);
		p.ret += ft_print_s(p.s);
	}
	if (c == 'd')
	{
		p.n = va_arg(ap, int);
		p.ret += ft_print_d(p.n);
	}
	return (p.ret);
}

int	ft_printf(const char *s, ...)
{
	int		i;
	int		rett;
	va_list	ap;

	i = 0;
	rett = 0;
	va_start(ap, s);
	while (s[i])
	{
		if (s[i] == '%')
		{
			i++;
			rett += ft_stock(s[i], ap);
		}
		else if (s[i] != '%')
			rett += write (1, &s[i], 1);
		i++;
	}
	va_end(ap);
	return (rett);
}


int	main()
{
	char			*s;
	unsigned int	x;
	int		d;

	s = "Hello everyone";
	x = 73;
	d = -65979;

	ft_printf("%s our tempeture is %d degree and our adresse is %x Byee\n", s, d, x);
	printf("%s our tempeture is %d degree and our adresse is %x Byee\n", s, d, x);
	printf("%d\n", printf("%s tempeture %d degree and adresse %x Byee\n", s, d, x));
	printf("%d\n", ft_printf("%s tempeture %d degree and adresse %x Byee\n", s, d, x));
	return (0);
}
