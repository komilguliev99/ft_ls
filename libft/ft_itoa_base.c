/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcapers <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 22:21:09 by dcapers           #+#    #+#             */
/*   Updated: 2020/02/27 22:21:11 by dcapers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int			calc_length(long long int nbr, int base)
{
	int		len;

	len = 0;
	while (nbr /= base)
		len++;
	return (len);
}

char				value_of(int n, int flag)
{
	if (n >= 0 && n <= 9)
		return ('0' + n);
	return ('a' + (n - 10) - (flag ? 32 : 0));
}

char				*ft_itoa_base(long long int nbr, int base, int flag)
{
	char		*res;
	int			len;
	int			to;

	if (nbr < -9223372036854775807)
		return (ft_strdup("-9223372036854775808"));
	to = base == 10 && nbr < 0;
	len = calc_length(nbr, base) + to + 1;
	if (!(res = malloc(len + 1)))
		return (NULL);
	if (to)
		res[0] = '-';
	res[len] = '\0';
	nbr = nbr < 0 ? -nbr : nbr;
	while (len > to)
	{
		res[len - 1] = value_of(nbr % base, flag);
		len--;
		nbr /= base;
	}
	return (res);
}
