/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avant.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 13:49:52 by thi-phng          #+#    #+#             */
/*   Updated: 2021/11/05 15:09:48 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>
//#include <stdlib.h>


typedef struct	s_type
{
	char			*s;
	int				d;
	unsigned int	x;
	int				ret;
}				t_type;

void	init(t_type *f)
{
	f->s = 0;
	f->d = 0;
	f->x = 0;
	f->ret = 0;
}

int	ft_printf_s(char *s)
{
	int		i = 0;
	
	while (s && s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
	return (i);
}

void	put_d(int d)
{
	long int	n;
	char		*base = "0123456789";

	n = d;
	if (n < 0)
	{
		write(1, "-", 1);
		n = -n;
	}
	if (n >= 10)
		put_d((int)n / 10);
	write(1, &base[(n % 10)], 1);
}

int	size_d(int d)
{
	int	i = 1;
	if (d < 0)
		i++;
	while (d / 10)
	{
		d = d / 10;
		i++;
	}
	return (i);
}

int	ft_printf_d(int d)
{
	put_d(d);
	return (size_d(d));
}


void	put_x(unsigned int x)
{
	char	*base = "0123456789abcdef";

	if (x >= 16)
		put_x(x / 16);
	write(1, &base[(x % 16)] , 1);
}

int	size_x(unsigned int x)
{
	int	i = 1;
	while (x / 16)
	{
		x = x / 16;
		i++;
	}
	return (i);
}


int	ft_printf_x(unsigned int x)
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
		p.ret += ft_printf_s(p.s);
	}
	if (c == 'd')
	{
		p.d = va_arg(ap, int);
		p.ret += ft_printf_d(p.d);
	}
	if (c == 'x')
	{
		p.x = va_arg(ap, unsigned int);
		p.ret += ft_printf_x(p.x);
	}
	return (p.ret);
}

int	ft_printf(const char *s, ...)
{
	int		i = 0;
	int		ret = 0;
	va_list	ap;

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
	int		n = -3287;
	char *s = "hello coucou";
	unsigned int x = 12;

	printf("%d\n", ft_printf("Tho oi %s cac em %d tuoi, and %x\n", s, n, x));
	printf("%d\n", printf("Tho oi %s cac em %d tuoi, and %x\n", s, n, x));
	printf("%d\n", ft_printf("%s\n", s));
	printf("%d\n", printf("%s\n", s));
	return (0);
}
