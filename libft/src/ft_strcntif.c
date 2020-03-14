/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcntif.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcapers <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 13:30:50 by dcapers           #+#    #+#             */
/*   Updated: 2019/09/17 14:16:37 by dcapers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strcntif(char **av, int (*f)(char *))
{
	int		count;

	if (!av || !*av || !f)
		return (0);
	count = 0;
	while (av)
	{
		if (f(*av))
			count++;
		av++;
	}
	return (count);
}
