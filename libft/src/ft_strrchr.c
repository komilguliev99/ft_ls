/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcapers <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 15:33:06 by dcapers           #+#    #+#             */
/*   Updated: 2019/09/10 18:08:36 by dcapers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*ptr;
	size_t	l;

	ptr = (char *)s;
	l = ft_strlen(s) + 1;
	while (l-- > 0)
		if (ptr[l] == c)
			return (ptr + l);
	return (NULL);
}
