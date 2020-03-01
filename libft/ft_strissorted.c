/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strissorted.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcapers <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 13:12:07 by dcapers           #+#    #+#             */
/*   Updated: 2019/09/17 13:26:11 by dcapers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strissorted(const char **av, int ac)
{
	int		i;
	int		asc;
	int		desc;

	i = 0;
	asc = 0;
	desc = 0;
	if (!av || !*av || ac < 0)
		return (0);
	while (i < ac - 1)
	{
		if (ft_strcmp(av[i], av[i + 1]) >= 0)
			desc++;
		if (ft_strcmp(av[i], av[i + 1]) <= 0)
			asc++;
		i++;
	}
	if (desc == ac - 1 || asc == ac - 1)
		return (1);
	return (0);
}
