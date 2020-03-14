/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kolya <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 00:40:16 by kolya             #+#    #+#             */
/*   Updated: 2019/09/17 13:36:13 by dcapers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*p1;
	char		*p2;
	size_t		i;

	p1 = (char *)dest;
	p2 = (char *)src;
	if (!n || src == dest)
		return (dest);
	i = 0;
	while (i < n)
	{
		p1[i] = p2[i];
		i++;
	}
	return (dest);
}
