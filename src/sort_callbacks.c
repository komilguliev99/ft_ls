/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_callbacks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcapers <dcapers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 11:47:33 by ds107             #+#    #+#             */
/*   Updated: 2020/03/07 18:15:59 by dcapers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		sort_asc_name(t_file *f1, t_file *f2)
{
	if (ft_strcmp(f1->name, f2->name) <= 0)
		return (1);
	return (0);
}

int		sort_desc_name(t_file *f1, t_file *f2)
{
	if (ft_strcmp(f1->name, f2->name) >= 0)
		return (1);
	return (0);
}

int		sort_ascn_time(t_file *f1, t_file *f2)
{
	if (f1->last_d - f2->last_d == 0)
	{
		if (ft_strcmp(f1->name, f2->name) <= 0)
			return (1);
		else
			return (0);
	}
	else if (f1->last_d - f2->last_d > 0)
		return (1);
	else
		return (0);
}

int		sort_descn_time(t_file *f1, t_file *f2)
{
	if (f1->last_d - f2->last_d == 0)
	{
		if (ft_strcmp(f1->name, f2->name) >= 0)
			return (1);
		else
			return (0);
	}
	else if (f1->last_d - f2->last_d < 0)
		return (1);
	else
		return (0);
}
