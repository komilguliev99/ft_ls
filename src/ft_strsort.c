/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcapers <dcapers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 16:37:25 by dcapers           #+#    #+#             */
/*   Updated: 2020/03/03 16:43:34 by dcapers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_strsort(char **args, int ac)
{
	int		i;
	int		flag;
	char	*swap;

	flag = 1;
	while (flag)
	{
		flag = 0;
		i = 0;
		while (i < ac - 1)
			if (ft_strcmp(args[i], args[i + 1]) > 0)
			{
				swap = args[i];
				args[i] = args[i + 1];
				args[i++ + 1] = swap;
				flag = 1;
			}
			else
				i++;
	}
}