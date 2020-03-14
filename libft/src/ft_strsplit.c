/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcapers <dcapers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 15:34:56 by dcapers           #+#    #+#             */
/*   Updated: 2020/03/13 17:48:44 by dcapers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int		ft_wordcount(char const *s, char c)
{
	size_t	i;
	int		count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
		if (s[i] != c)
		{
			while (s[i] != c && s[i] != '\0')
				i++;
			count++;
		}
		else
			i++;
	return (count);
}

static char		**clear_mem(char **wds)
{
	while (wds--)
		free(*wds);
	free(wds);
	return (NULL);
}

char			**ft_strsplit(char const *s, char c)
{
	char			**res;
	size_t			i;
	unsigned int	st;
	int				w_c;

	if (!s)
		return (NULL);
	w_c = ft_wordcount(s, c);
	i = 0;
	if (!(res = (char **)malloc(sizeof(char *) * (w_c + 1))))
		return (NULL);
	while (s[i] != '\0')
		if (s[i] != c)
		{
			st = (unsigned int)i;
			while (s[i] != c && s[i] != '\0')
				i++;
			if ((*res = ft_strsub(s, st, i - st)) == NULL)
				return (clear_mem(res));
			res++;
		}
		else
			i++;
	*res = NULL;
	return (res - w_c);
}
