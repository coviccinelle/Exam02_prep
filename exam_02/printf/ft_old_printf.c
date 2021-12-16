/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 14:24:23 by thi-phng          #+#    #+#             */
/*   Updated: 2021/10/25 16:53:25 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

typedef struct	s_type
{
	char			*s;
	long int		d;
	unsigned int	x;
}				t_type;

typedef struct	s_flags
{
	int		width;
	char	type;
	t_type	z;
}				t_flags;

void	init_struct(t_flags *f)
{
	f->width = 0;
	f->type = 0;
}

int		find_me(char c, const char *str)
{
	int n;

	n = 0;
	while (str[n])
	{
		if (str[n] == c)
			return (c);
		n++;
	}
	return (0);
}

int		get_width(t_flags *f, const char *s, int *n)
{
	f->width = f->width * 10 + (s[*n] - '0');
	(*n)++;
	return (0);
}

int	ft_putstr(const char *str)
{
	int ret;

	ret = 0;
	while (str[ret])
	{
		ret += write(1, &str[ret], 1);
	}
	return (ret);
}

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

int	ft_hexa(unsigned int n)
{
	int		ret;
	char	*s;
	char	c;

	s = "0123456789abcdef";
	ret = 0;
	if (n / 16)
		ret += ft_hexa(n / 16);
	c = s[(n % 16)];
	ret += write(1, &c, 1);
	return (ret);
}

void	stock_va_arg(t_flags *f, va_list ap)
{
	f->z.s = "(null)";
	f->z.d = 0;
	f->z.x = 0;
	if (f->type == 's')
		f->z.s = va_arg(ap, char *);
	if (f->type == 'd')
		f->z.d = va_arg(ap, int);
	if (f->type == 'x')
		f->z.x = va_arg(ap, unsigned int);
	if (!f->z.s)
		f->z.s = "(null)";
	return ;
}

int		print_type(va_list ap, t_flags *f)
{
	stock_va_arg(f, ap);
	if (f->type == 's')
		return (ft_putstr(f->z.s));
	if (f->type == 'd')
		return (ft_putnbr(f->z.d));
	if (f->type == 'x')
		return (ft_hexa(f->z.x));
	return (0);
}

int		parsing(const char *s, va_list ap, int *n)
{
	t_flags		f;

	init_struct(&f);
	(*n)++;
	while (find_me(s[*n], "0123456789"))
		get_width(&f, s, n);
	if (find_me(s[*n], "sdx"))
	{
		f.type = s[*n];
		(*n)++;
		return (print_type(ap, &f));
	}
	return (0);
}

int	ft_printf(const char *s, ...)
{
	va_list		ap;
	int			ret;
	int			n;

	ret = 0;
	n = 0;
	va_start(ap, s);
	while (s[n])
	{
		if (s[n] && s[n] == '%')
			ret += parsing(s, ap, &n);
		if (s[n] && s[n] != '%')
		{
			ret += write(1, &s[n], 1);
			n++;
		}
	}
	va_end(ap);
	return (ret);
}

#include <stdio.h>

int	main(void)
{
	int a = 627;
	ft_printf("Hello coucou how are you %s Long time no see, you're %d years old right? And your adress is %x Or am I wrong? \n", "Rob", 302, a);
	printf("Hello coucou how are you %s Long time no see, you're %d years old right? And your adress is %x Or am I wrong? \n", "Rob", 302, a);
}
