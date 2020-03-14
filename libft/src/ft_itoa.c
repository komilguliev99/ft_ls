/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcapers <dcapers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 15:36:16 by dcapers           #+#    #+#             */
/*   Updated: 2020/03/14 14:53:39 by dcapers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_strrmove(char *s, int l, int from)
{
	while (l-- > from)
		s[l + 1] = s[l];
}

int				ft_numcount(int nb)
{
	int		l;

	l = 1;
	if (nb < 0)
		l++;
	while (nb || l == 1)
	{
		nb /= 10;
		l++;
	}
	return (l);
}

char			*ft_itoa(int nb)
{
	char	*res;
	int		l;
	int		sg;

	l = 0;
	if (!(res = (char *)malloc(ft_numcount(nb))))
		return (NULL);
	if (nb == -2147483648)
		return (ft_strdup("-2147483648"));
	ft_memset(res, '\0', 12);
	if (nb < 0)
	{
		nb = -nb;
		res[0] = '-';
		l++;
	}
	sg = l;
	while (nb || l == 0)
	{
		ft_strrmove(res, l, sg);
		res[sg] = nb % 10 + 48;
		nb /= 10;
		l++;
	}
	return (res);
}
