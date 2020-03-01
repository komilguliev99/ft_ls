/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kolya <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 13:31:40 by kolya             #+#    #+#             */
/*   Updated: 2019/09/12 16:08:26 by dcapers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *hstk, const char *nd)
{
	if (*nd == '\0')
		return ((char *)(hstk));
	while (ft_strncmp(hstk, nd, ft_strlen(nd)) != 0 && *hstk != '\0')
		hstk++;
	if (*hstk == '\0' && *hstk != nd[0])
		return (NULL);
	return ((char *)hstk);
}
