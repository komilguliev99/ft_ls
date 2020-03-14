/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_callbacks2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcapers <dcapers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/14 16:51:25 by dcapers           #+#    #+#             */
/*   Updated: 2020/03/14 16:55:14 by dcapers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			sort_by_size(t_file *f1, t_file *f2)
{
	if (f1->byte_size <= f2->byte_size)
		return (1);
	return (0);
}

int			sort_ascn_creat(t_file *f1, t_file *f2)
{
	if (f1->tm_creat - f2->tm_creat == 0)
	{
		if (ft_strcmp(f1->name, f2->name) <= 0)
			return (1);
		else
			return (0);
	}
	else if (f1->tm_creat - f2->tm_creat > 0)
		return (1);
	else
		return (0);
}

int			sort_descn_creat(t_file *f1, t_file *f2)
{
	if (f1->tm_creat - f2->tm_creat == 0)
	{
		if (ft_strcmp(f1->name, f2->name) >= 0)
			return (1);
		else
			return (0);
	}
	else if (f1->tm_creat - f2->tm_creat < 0)
		return (1);
	else
		return (0);
}

int			sort_ascn_access(t_file *f1, t_file *f2)
{
	if (f1->tm_access - f2->tm_access == 0)
	{
		if (ft_strcmp(f1->name, f2->name) <= 0)
			return (1);
		else
			return (0);
	}
	else if (f1->tm_access - f2->tm_access > 0)
		return (1);
	else
		return (0);
}

int			sort_descn_access(t_file *f1, t_file *f2)
{
	if (f1->tm_access - f2->tm_access == 0)
	{
		if (ft_strcmp(f1->name, f2->name) >= 0)
			return (1);
		else
			return (0);
	}
	else if (f1->tm_access - f2->tm_access < 0)
		return (1);
	else
		return (0);
}
