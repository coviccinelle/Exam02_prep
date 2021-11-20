/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 13:59:04 by thi-phng          #+#    #+#             */
/*   Updated: 2021/10/18 14:37:19 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

# define $NOT_FOUND -1
# define $ENDL '\n'
# define $ZERO '\0'


int	strclen(char *str, char c);
char	*ft_strndup(char *str, int n);
char	*ft_strjoin(char *s1, char *s2);
char	*return_value(char **overflow);
char    *get_next_line(int fd);

#endif
