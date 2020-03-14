/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcapers <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 17:55:21 by dcapers           #+#    #+#             */
/*   Updated: 2019/09/17 13:06:43 by dcapers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		is_whitesp(char c)
{
	if (c == ' ' || c == '\n' || c == '\t')
		return (1);
	return (0);
}

static char		*ft_strempty(size_t len)
{
	char	*r;

	if (!(r = (char *)malloc(len)))
		return (NULL);
	while (len--)
		r[len] = '\0';
	return (r);
}

char			*ft_strtrim(char const *str)
{
	char	*s;
	size_t	len;
	size_t	p;
	char	*res;

	p = 0;
	s = (char *)str;
	if (!str)
		return (NULL);
	len = ft_strlen(str);
	while (s && s[p] && s[p] != '\0' && is_whitesp(s[p]))
		p++;
	if (s[p] != '\0')
	{
		while (s[len - 1] && len > p && is_whitesp(s[len - 1]))
			len--;
		if (len - p > 0)
		{
			if ((res = ft_strsub(s, p, len - p)) != NULL)
				return (res);
			else
				return (NULL);
		}
	}
	return (ft_strempty(1));
}
