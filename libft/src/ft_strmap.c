/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcapers <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 16:21:29 by dcapers           #+#    #+#             */
/*   Updated: 2019/09/13 18:16:25 by dcapers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*nstr;
	size_t	i;

	i = 0;
	if (s == NULL)
		return (NULL);
	if (!(nstr = (char *)malloc(ft_strlen(s) + 1)))
		return (NULL);
	while (s[i] != '\0')
	{
		nstr[i] = f(s[i]);
		i++;
	}
	nstr[i] = '\0';
	return (nstr);
}
