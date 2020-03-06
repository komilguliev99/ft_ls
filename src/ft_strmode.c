/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcapers <dcapers@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 21:29:10 by ds107             #+#    #+#             */
/*   Updated: 2020/03/06 21:54:47 by dcapers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_fillmode(char *res, int i, int num)
{
	int		j;
	char	s[4];

	s[0] = 'r';
	s[1] = 'w';
	s[2] = 'x';
	j = i - 3;
	while (i > j)
	{
		if (num % 2 == 1)
			res[i] = s[i - j - 1];
		else
			res[i] = '-';
		i--;
		num /= 2;
	}
}

char		*ft_strmode(unsigned int mode)
{
	char		*res;
	int			i;

	if (!(res = malloc(10)))
		exit (0);
	i = 3;
	while (i)
	{
		ft_fillmode(res, i * 3 - 1, mode % 8);
		mode /= 8;
		i--;
	}
	return (res);
}
