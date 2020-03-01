/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kolya <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 13:31:40 by kolya             #+#    #+#             */
/*   Updated: 2019/09/14 13:38:18 by dcapers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *hstk, const char *nd,
	size_t n)
{
	size_t		i;

	i = 0;
	if (*nd == '\0')
		return ((char *)hstk);
	while (ft_strncmp(hstk + i, nd, ft_strlen(nd)) != 0 && hstk[i] != '\0'
			&& i < n)
		i++;
	if (*(hstk + i) == '\0' || (ft_strlen(nd) + i > n))
		return (NULL);
	return ((char *)(hstk + i));
}
