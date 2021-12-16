/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   micro_paint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 17:51:49 by thi-phng          #+#    #+#             */
/*   Updated: 2021/12/16 18:00:18 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

typedef struct 

void    ft_putchar(char c)
{
    write(1, &c, 1);
}

void    ft_putstr(char *str)
{
    int i = 0;

    while (str[i])
        ft_putchar(str[i++]);
}

int main(int ac, char **av)
{
    t_a a;

    a.ret = 0;
    if (ac != 2)
    {
        ft_putstr("Error: agrument\n");
        return (1);
    }
    if (!(a.file = fopen(av[1], "r"))))
    {
        ft_putstr("Error: Operation file corrupted\n");
        return (1);
    }
    execute(&a);
    fclose(a.file);
    if (a.ret == 1)
        ft_putstr("Error: Operation file corrupted\n");
    return (a.ret);
}