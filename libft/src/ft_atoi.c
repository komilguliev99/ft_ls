/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcapers <dcapers@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 22:20:39 by dcapers           #+#    #+#             */
/*   Updated: 2020/03/01 17:33:12 by dcapers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long int		well_returned(unsigned long long res, int sg,
		int count)
{
	if (count >= 19)
		return (sg == -1 ? 0 : -1);
	else if (res > 9223372036854775807)
		return (sg == -1 ? 0 : -1);
	else
		return (res * sg);
}

long int			ft_atoi(const char *str)
{
	int					ng;
	unsigned long long	res;
	int					count;

	res = 0;
	ng = 1;
	count = 0;
	while (*str && (*str == ' ' || *str == '\n' || *str == '\t' ||
				*str == '\r' || *str == '\f' || *str == '\v'))
		str++;
	if (*str == '-')
		ng = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (ft_isdigit(*str) && *str != '\0')
	{
		res = (res * 10) + (unsigned long long)(*str - '0');
		str++;
		count++;
	}
	return (well_returned(res, ng, count));
}
