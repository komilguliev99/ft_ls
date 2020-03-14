/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kolya <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 00:45:45 by kolya             #+#    #+#             */
/*   Updated: 2019/09/10 15:17:08 by dcapers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char		*p1;
	const unsigned char	*p2;
	size_t				i;

	p1 = (unsigned char*)dst;
	p2 = (unsigned char*)src;
	i = 0;
	while (i < n)
	{
		p1[i] = p2[i];
		if (p2[i] == (unsigned char)c)
			return (p1 + i + 1);
		i++;
	}
	return (NULL);
}
