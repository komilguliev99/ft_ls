/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcapers <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 16:08:04 by dcapers           #+#    #+#             */
/*   Updated: 2019/09/13 18:13:41 by dcapers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t sz)
{
	char	*str;

	str = (char *)malloc(sz + 1);
	if (str == NULL)
		return (NULL);
	ft_memset(str, (int)'\0', sz + 1);
	return (str);
}
