/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kolya <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 13:22:03 by kolya             #+#    #+#             */
/*   Updated: 2019/09/14 17:29:33 by dcapers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t sz)
{
	size_t	l_dst;
	size_t	l_src;
	size_t	res;
	size_t	i;

	l_dst = ft_strlen(dst);
	l_src = ft_strlen(src);
	if (sz >= l_dst)
		res = l_dst + l_src;
	else
		res = sz + l_src;
	i = 0;
	while (l_dst + i + 1 < sz && src[i] != '\0')
	{
		dst[l_dst + i] = src[i];
		i++;
	}
	dst[l_dst + i] = '\0';
	return (res);
}
